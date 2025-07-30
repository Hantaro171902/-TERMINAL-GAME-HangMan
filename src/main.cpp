#include <iostream>
#include <ctime> // Cần cho time(NULL) để khởi tạo srand
#include "menu.hpp"
#include "cursor_input.hpp"
#include "ultils.hpp"
#include "words.hpp"

using namespace std;

int main(){
    // Khởi tạo bộ tạo số ngẫu nhiên MỘT LẦN DUY NHẤT khi chương trình bắt đầu
    srand(time(NULL));
    cerr << "DEBUG: srand initialized with time(NULL)." << endl;

    // Tải dữ liệu từ vào bộ nhớ MỘT LẦN DUY NHẤT khi chương trình bắt đầu
    load_word_data();
    // DEBUG: Kiểm tra xem từ đã được tải chưa
    cerr << "DEBUG: Words loaded: " << words_animals.size() << " animals, "
         << words_countries.size() << " countries, "
         << words_fruits.size() << " fruits, "
         << words_periodic.size() << " periodic, "
         << words_states.size() << " states." << endl;


    // Thiết lập console
    toggle_cursor(false); // Ẩn con trỏ
    // console_size(800,600); // Dòng này chỉ hoạt động trên Windows, có thể bỏ qua trên Linux/macOS

    // Vòng lặp game chính, gọi menu để người chơi tương tác
    while(true){
        menu();
    }

    return 0;
}
