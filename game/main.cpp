#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QFrame>
#include <QHBoxLayout>

int main(int argc, char *argv[]) {
    // QApplication 객체를 생성하여 Qt 애플리케이션을 초기화합니다.
    QApplication app(argc, argv);

    // 기본적인 QWidget 객체를 생성하여 창을 만듭니다.
    QWidget window;

    // 창의 제목 설정
    window.setWindowTitle("Knight's Tour");

    // 창 크기 설정 (가로 600px, 세로 500px)
    window.resize(600, 500);

    // 창의 배경 색을 검은색으로 설정
    window.setStyleSheet("background-color: black;");

    // QVBoxLayout을 사용하여 세로 방향 레이아웃을 설정합니다.
    QVBoxLayout *layout = new QVBoxLayout(&window);

    // "knight's tour" 텍스트를 설정하는 QLabel 생성
    QLabel *titleLabel = new QLabel("Knight's Tour", &window);
    titleLabel->setAlignment(Qt::AlignCenter);  // 텍스트를 가운데 정렬
    titleLabel->setStyleSheet("color: white; font-size: 48px;");  // 텍스트 색상과 크기 설정

    // 텍스트를 레이아웃에 추가
    layout->addWidget(titleLabel);

    // 두 개의 QFrame을 생성하여 'game'과 'example'을 나타냅니다.
    QFrame *gameFrame = new QFrame(&window);
    QFrame *exampleFrame = new QFrame(&window);

    // 각 프레임에 스타일 설정 (배경색, 크기 등)
    gameFrame->setStyleSheet("background-color: darkgray; border: 1px solid white;");
    exampleFrame->setStyleSheet("background-color: gray; border: 1px solid white;");
    
    // 레이아웃에 'game'과 'example' 프레임 추가
    layout->addWidget(gameFrame);
    layout->addWidget(exampleFrame);

    // 레이아웃 설정을 통해 창을 화면에 표시
    window.setLayout(layout);

    // 창을 화면에 표시
    window.show();

    // 애플리케이션 실행 (이벤트 루프 시작)
    return app.exec();
}
