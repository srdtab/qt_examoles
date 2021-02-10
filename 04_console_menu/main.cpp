#include <iostream>
#include <string>

using namespace std;

const unsigned char number_of_items = 13; //Всего опций
const unsigned char frame_size = 5; //Сколько строк (опций) умещается на экране

enum KEYS{ //Наверное, для экономии места на ардуине можно отказаться от всяких энумов и просто возвращать волшебные цифры
    UP,
    DOWN,
    SELECT,
    OTHER
};

//Считывает нажатую кнопку и возвращает то, что было нажато
KEYS get_key(){
    char c = getchar();
    KEYS result;
    switch (c){
    case 'u': result =  UP; break;
    case 'd': result =  DOWN; break;
    case 's': result =  SELECT; break;
    default: result =  OTHER; break;
    }
    getchar(); //Особенность моего терминала Убунты
    return result;
}

class BoundInt{
public:
    //initializer list - видел такую сокращенную запись конструктора у крутых пацанов, вот решил сам попробовать
    BoundInt(int value, int min, int max) : value_{value}, min_{min}, max_{max} {bind_();}
    //Префиксный инкремент (++boundInt)
    BoundInt& operator++()
    {
       value_++;
       bind_();
       return *this;
    }
    //Префиксный декремент (--boundInt)
    BoundInt& operator--()
    {
       value_--;
       bind_();
       return *this;
    }
    //Постфиксный инкремент (boundInt++ или boundInt+=5)
    BoundInt operator++(int add_value){
        auto temp_object = *this;
        if(add_value == 0)
            this->value_++;
        else
            this->value_+=add_value;
        this->bind_();
        return temp_object;
    }
    //Постфиксный декремент (boundInt-- или boundInt-=5)
    BoundInt operator--(int substr_value){
        auto temp_object = *this;
        if(substr_value ==0)
            this->value_--;
        else
            this->value_-=substr_value;
        this->bind_();
        return temp_object;
    }
    //Охреневший оператор автоматического приведения к инту, чтобы мы могли вставлять объект нашего класса как номер элемента массива
    operator int() const {return value_;}

    int value() const {return value_;}

    void setValue(int value) {value_ = value; bind_();}


private:
    int value_{0};
    int min_{0};
    int max_{0};
    void bind_(){
        if(value_>max_)
            value_=max_;
        if(value_<min_)
            value_=min_;
    }
};

void draw_menu(int selected_option,
          int total_options,
          int frame_size,
          const string* options_texts){
    printf("\033c"); //Чистит экран терминала Линукса
    //cout<<selected_option<<endl;
    int page = selected_option / frame_size; //Страница для отображения
    int first_index = page * frame_size; //Номер первой строки страницы в массиве
    int last_index = first_index + frame_size; //Номер последней строки страницы в массиве
    if(last_index > total_options)
        last_index = total_options;
    for(int i = first_index; i < last_index; i++){
        i == selected_option ? cout << ">>>" : cout << "   ";
        cout<<options_texts[i]<<endl;
    }
}

int main()
{
    string items[number_of_items];

    for(int i = 0; i< number_of_items; i++) //Заполняем
        items[i] = string("Опция №") + to_string(i);

    KEYS key_pressed;
    BoundInt selected_option(0,0,number_of_items-1);
    while(true){
        draw_menu(selected_option.value(),number_of_items,frame_size,items);
        key_pressed = get_key();
        if(key_pressed==UP) selected_option--;
        else if(key_pressed==DOWN) ++selected_option;
        else break;
    }
}
