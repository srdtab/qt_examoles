#include <iostream>

//ВОТ ТУТ СКОРЕЕ ВСЕГО БУДЕТ ОШИБКА НА ВИНДЕ, ПРИДЕТСЯ НАЙТИ ПОДХОДЯЩУЮ БИБЛИОТЕКУ ДЛЯ РЕАЛИЗАЦИИ ВВОДА
//И ПЕРЕДЕЛАТЬ ФУНКЦИЯ, ОТВЕЧАЮЩУЮ ЗА ВВОД С ЭКРАНА
#include <ncurses.h>

// Я всё написал в main.cpp, но вообще так не делают, лучше разбить на отдельные файлы. Но так тебе будет проще собрать в студии

//! ================================
//! Перечисляемый тип для расстояния
//! ================================
enum Direction{
    Up      = 0,
    Down    = 1,
    Left    = 2,
    Right   = 3,
};

//! Инициализация служебных методов библиотеки Ncurses
void ncursesInit(){
    initscr();
    cbreak();
    noecho();
}

int getDirection(){
    int answer =  getch();
    switch (answer) {
    case KEY_UP: return (int) Up; break;
    case KEY_DOWN: return (int) Down; break;
    case KEY_LEFT: return (int) Down; break;
    case KEY_RIGHT: return (int) Down; break;
    default: return -1;
    }
}

//! ============================================
//! Функция, возарващающая случайное направление
//! ============================================
Direction randomDirecton(){
    //Эта страшная строчка преобразует случайное число от 0 до 3 в одно из направлений (Direction)
    //и возврашает это значение
    return static_cast<Direction>(rand()%4);
}

//! ================================================================================================
//! Структура, соответствующая "фрагменту" тела змеи. Будет использвоаться, внезапно, в классе Snake
//! ================================================================================================
struct Part{
    int x = 0;      // координата по x
    int y = 0;      // координата по y
    Part* prev;     // указатель на предыдущий фрагмент
    Part* next;     // указатель на следующий фрагмент
    // Указатели на предыдущий и следующий держим, чтобы потом тело змеи представлять как двусвязный список


    //! Статический метод.
    //! Создает новый фрагмент радом с фрагментом Part и возвращает указатель на него.
    //! direction определяет, с какой стороны от part будет новый созданный фрагмент
    static Part* getAdjacent(const Part* part, Direction direction = randomDirecton()){
        if(!part)
            return nullptr;
        Part* newPart = new Part(*part);
        switch(direction){
            case Up:
                newPart->y--;
                break;
            case Down:
                newPart->y++;
                break;
            case Left:
                newPart->x--;
                break;
            case Right:
                newPart->x++;
                break;
        }
        return newPart;
    }
};

class Field; //Заранее объявим (forvard declareatin) класс Field, чтобы могли его записать в друзья к змейке

//! =============================
//! Класс, соответствующей змейке
//! =============================
class Snake{
    friend class Field;
public:
    //! Конструктор. На вход подаем максимальные высоту и ширину поля, по которому может ползать змейка
    Snake(int maxHeight, int maxWidth) : height_(maxHeight), width_(maxWidth){
        initBody_();
    };

    //! Переместить змейку в направлении direction
    //! Параметр gtow определяет, вырсола ли змейка за этот такт (съела ли бонус)
    //! Возвращает true, если новое положение змейки допустимо, иначе - false
    bool move(Direction direction, bool grow = false){
        if(!head_)
            return false;

        if(!grow){ //Удаляем последний элемент змейки
            last_ = last_->prev;
            delete last_->next;
            last_->next = nullptr;
        }

        Part* newHead = Part::getAdjacent(head_,direction);
        if(!isLegal_(newHead))
            return false;
        head_->prev = newHead;
        newHead->next = head_;
        head_ = newHead;
        return true;
    }


private:
    //! Максимальные высота и ширина поля, по которому змейка может ползать
    int height_ = 0;
    int width_ = 0;

    //! Текущая и максимальная длины змейки
    int currentLength_ = 0;
    const int maxLength_ = 20;

    //! Проверяет на то, легальна ли позиция фрагмента тела змейки
    //! (нет ли пересечений с другими фрагментами или не выходит ли за край карты)
    bool isLegal_(const Part* part){
        if(part->x >= height_
                | part->x <= 0
                | part->y >= width_
                | part->y <= 0)
            return false;

        bool intersections = false;
        Part* currentlyChecking = head_;
        while(currentlyChecking !=nullptr){
            if(currentlyChecking->x == part->x & currentlyChecking->y == part->y){
                 intersections = true;
                return false;
            }
            currentlyChecking = currentlyChecking->next;
        }
        return true;
    }

    //! Заполняет тело змеи
    void initBody_(){ //Особо не парился, в каких клетках она зиначально заполняется
        head_ = new Part;
        head_->x = width_ / 2;
        head_->y = height_ / 2;
        Part* neck = Part::getAdjacent(head_);
        head_->prev = nullptr;
        head_->next = neck;
        neck->prev = head_;
        neck->next = nullptr;
        currentLength_ = 2;
        last_ = neck;
    };

    //! Указатель на голову (первый сегмент) змейки
    Part* head_ = nullptr;

    //! Указатель на последний сегмент змейки
    Part* last_ = nullptr;


};


//! ===========================
//! Класс, соответствующий полю
//! ===========================
class Field
{
    friend class Snake;
public:
    //! Конструктор. Задаем длину и ширину поля (по умолчанию 20х20), выделяем динамическую память под клеточки
    Field(int width = 20, int height = 20) : width_(width), height_(height){
        //Выделяем память под клетки
        square_ = new char*[height_];
        for(int h = 0; h <= width_; h++) //<= потому что последним будет стоять '\0', чтобы нормально выводить строки
            square_[h] = new char[width_];

        //Проставляем спецсимволы конца строки
        for(int h = 0; h < height_; h++)
            square_[h][width_] = '\0';

        //Создаем змейку
        snake_ = new Snake(height_,width_);
    }

    //! Деструктор. Удаляем всё, что нужно, чтобы не было утечек памяти
    ~Field(){
        for(int i = 0; i < height_; ++i)
            delete[] square_[i];
        delete[] square_;

        if (snake_ != nullptr){
            delete snake_;
        }
    }

    //! Рисуем поле
    void draw(){

        //Рисуем клетки поля (по хорошему из бы не перерисчитывать каждый раз, а прерсчитывать только то, что поменялось, но пока так)
        initSqures_();
        //Фиксируем, где змейка
        accountForSnake_();
        for(int h = 0; h < height_; h++)
           // std::cout << square_[h] << std::endl;
            printw(square_[h]);
    }

    //TODO
    void moveSnake(Direction direction){
        snake_->move(direction,true);
    }

    void dbg(){
        static int d = 0;
        d++;
        if (d >10) d = 0;
        square_[d][d] = 's';
    }

private:
    //! Инициализация клеток поля (пока без змеи)
    void initSqures_(){
        //верхняя и нижняя границы
        for(int w = 0; w < width_; w++){
            square_[0][w] = '#';
            square_[height_-1][w] = '#';
        }
        //Все остальные
        for(int h = 1; h < height_-1; h++){
            square_[h][0] = '#';
            square_[h][width_-1] = '#';
            for(int w = 1; w < width_ - 1; w++)
                square_[h][w] = ' ';
        }
    }

    //! Делаем поправку на змейку
    void accountForSnake_(){
        if(snake_->head_ == nullptr)
            return;
        square_[snake_->head_->x][snake_->head_->y] = '0';
        Part* part = snake_->head_->next;
        while(part != nullptr){
            square_[part->x][part->y] = '*';
            part = part->next;
        }
    }

    //! Ширина
    int width_ = 0;
    //! Высота
    int height_ = 0;
    //! Клетки поля
    char** square_;

    //! Указатель на змейку, ползающую по полю
    Snake* snake_ = nullptr;
};

int main()
{
    //ncursesInit();
    Field field;

    while(true){
        std::system("clear");
        field.draw();
        field.dbg();

        int input = getDirection();
        if (input == -1)
            continue;

        field.moveSnake(static_cast<Direction>(input));
    }
}
