#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[]) {
    // QApplication 객체를 생성하여 Qt 애플리케이션을 초기화합니다.
    QApplication app(argc, argv);

    // 기본적인 QWidget 객체를 생성하여 창을 만듭니다.
    QWidget window;

    // 창의 제목 설정
    window.setWindowTitle("knight's tour");

    // 창 크기 설정 (가로 400px, 세로 300px)
    window.resize(400, 300);

    // 창을 화면에 표시
    window.show();

    // 애플리케이션 실행 (이벤트 루프 시작)
    return app.exec();
}
