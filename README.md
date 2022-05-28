# Hero Game
## Mục lục
* [Giới thiệu](#general-info)
* [Technologies](#technologies)
* [Setup](#setup)

## General info
Đây là một dự án lập trình game dành cho cuối kỳ môn lập trình nâng cao.
Game Hero là một game bắn quái vật lấy cảm hứng từ thể loại Shoot 'em up. Người chơi sẽ tiêu diệt quái vật để dành điểm số và cố gắng đứng đầu bảng thành tích

Video demo: 
## Technologies
Game được xây dựng bằng:
* Ngôn ngữ lập trình C++
* Thư viện SDL2
Với các kỹ thuật được sử dụng:
* Mảng, hàm
* STL container (stack, vector)
* Lớp, kế thừa
* Pointer, cấp phát và giải phóng bộ nhớ động
## Setup
Để tải và chạy dự án này cần có gnu compiler để biên dịch ngôn ngữ C++
Các bước:
* Tải và giải nén file zip của repository này, hoặc sử dụng git bash để clone file này về bằng câu lệnh
```
git clone 
```
* Nhấn tổ hợp phím Window + S, tìm kiếm "command prompt"
* Vào đường dẫn chứa repository folder, bằng câu lệnh 
```
cd {đường dẫn}
```
* Chạy câu lệnh để biên dịch chương trình và bắt đầu game, hoặc sử dụng makefile
```
g++ src/*.cpp -ISDL2\include -LSDL2\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -o SDL2/bin/Hero && start SDL2/bin/Hero.exe
```