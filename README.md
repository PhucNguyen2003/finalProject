# Hero Game
## Mục lục
* [Giới thiệu](#1-general-info)
* [Công cụ và kỹ thuật](#technologies)
* [Cài đặt](#setup)
* [Kết luận](#conclusion)

## 1 General info
Đây là một dự án lập trình game dành cho cuối kỳ môn lập trình nâng cao.

### 1.1 Mô tả về game
* Game Hero là một game bắn quái vật lấy cảm hứng từ thể loại Shoot 'em up. Người chơi sẽ tiêu diệt quái vật để dành điểm số và cố gắng đứng đầu bảng thành tích.
* Người chơi sẽ có 5 mạng, và phải né được người ngoài hành tinh di chuyển từ khắp trên bản đồ. Nếu bị va chạm vào người ngoài hành tinh hoặc đạn bắn thì sẽ bị mất một mạng. Nếu hết 5 mạng sẽ thua và kết thúc trò chơi.

### 1.2 Điều khiển game
* Sử dụng W A S D hoặc các phím mũi tên để di chuyển
* Sử dụng dấu cách để bắn đạn
* Sử dụng phím esc để trở về màn hình chính

### 1.3 Video demo game
Video giới thiệu game có thể được xem ở đây: https://youtu.be/dyge7_WwLLM

## Technologies

### 2.1 Công cụ sử dụng
Game được xây dựng bằng:
* Ngôn ngữ lập trình C++
* Thư viện SDL2

### 2.2 Kỹ thuật sử dụng để xây dựng game
Các kỹ thuật lập trình được sử dụng:
* Mảng, hàm
* STL container (stack, vector)
* Lớp
    * public, private, protected
    * Kế thừa
    * Hàm hằng
    * Hàm khởi tạo và hàm hủy
* Pointer, cấp phát và giải phóng bộ nhớ động
* Sinh ngẫu nhiên
* Tách hàm, tách file và quản lý các module theo file .cpp và file .h 
* Sử dụng thư viện đồ họa SDL2, SDL_image, SDL_mixer, SDL_ttf
* Log và báo cáo lỗi
* Xuất và nhập file .txt

### 2.3 Xử lý trong game
* Sinh ra và di chuyển
    * Nền động và sao trời tạo cảm giác tàu bay đang di chuyển
    * Địch sinh ngẫu nhiên và tiến tới
    * Đạn bắn được sinh khi người chơi ấn phím
* Xử lý va chạm
    * Va chạm giữa người chơi với
        * Đạn bắn của địch
        * Địch
    * Va chạm địch với
        * Đạn của người chơi
* Xử lý vụ nổ
    * Nổ của phi thuyền địch (có hiệu ứng)

### 2.4 Các giao diện khác
* Điểm số
    * Có màn hình điểm số riêng của 8 người chơi có điểm cao nhất
    * Điểm cập nhật liên tục trong lúc chơi
* Giao diện menu
    * nút 'Play game' để bắt đầu chơi
    * nút 'High score' để xem điểm cao nhất
    * nút 'Credit' để xem nguồn ảnh, âm thanh
    * nút 'Quit game' để thoát khỏi trò chơi
### 2.5 Âm thanh
* Nhạc nền
* Tiếng kêu của địch khi bắn
* Tiếng kêu của địch khi chết
* Tiếng kêu của đạn khi người chơi bắn
### 2.6 Xử lý fps
Fps được cố định ở mức 60 fps

## Setup

### 3.1 GNU và git
Để tải và chạy dự án này cần có gnu compiler để biên dịch ngôn ngữ C++
Các bước tải gnu có thể xem ở: https://www.youtube.com/watch?v=0HD0pqVtsmw&t
Sau đó có thể tải git để clone về máy, hoặc tải file zip của repository này
link tải git: https://git-scm.com/downloads

### 3.2 Tải và cài đặt game
* Tải và giải nén file zip của repository này, hoặc sử dụng git bash để clone file này về bằng câu lệnh
```
git clone https://github.com/PhucNguyen2003/finalProject.git
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

## Conclusion

### 3.1 Kết luận
* Đây là dự án đầu, vì còn thiếu kinh nghiệm trong quản lý code cũng như cách xử lý code theo hướng đối tượng, nên các lớp và hàm trong các module có chồng chéo và xây dựng không hợp lý
* Sử dụng thư viện đồ họa SDL hợp lý có thể tạo ra một số hiệu ứng hay hình ảnh khá độc đáo, do đó rất quan trọng trong phát triển game
* Có thể sử dụng những cấu trúc hay thuật toán cơ bản vẫn có thể tạo lên những game tuyệt vời.

### 3.2 Hướng phát triển
* Thêm quái, đạn, cũng như boss và game
* Thêm chế độ chơi, cốt truyện
* Bổ sung thêm vật phẩm
* Thay đổi độ khó game
* Tối ưu, cải tiến mã nguồn hơn nữa

### 3.3 Điều tâm đắc sau khi hoàn thiện chương trình
* Tìm kiếm hình ảnh rất khó nếu không có mắt thẩm mỹ, hoặc không có sự trợ giúp từ người khác am hiểu hơn
* Internet là một công cụ hiệu quả để tra cứu toàn bộ, song phải có chọn lọc và tìm tòi
