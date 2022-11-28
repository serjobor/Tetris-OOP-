#include "Tetris.h"
#include <iostream>

Tetris::Tetris() {
    area.resize(lines);
    for (std::size_t i{}; i < area.size(); ++i) { // создание игрового поля
        area[i].resize(cols);
    }

    figures = { new I(), new Z(), new S(), new T(), new L(), new J(), new O() };  // Массив фигур

    window = std::make_shared<sf::RenderWindow>(    // Окно игры
        sf::VideoMode(lines * w, lines * w),
        "Tetris",
        sf::Style::Titlebar | sf::Style::Close);
    window->setPosition(sf::Vector2i(500, 150));

    dirx = score = Line = { 0 };   // перемещение -><-; очки; линии
    rotate = gameover = { false }; // вращение фигуры; завершение игры
    timercount = speed = { 0.f };
    delay = { 0.3f };
    color = { 1 };

    std::uint32_t number = std::rand() % shapes;
    figures[number]->changeZarray(z);

    loadResources();
}

Tetris::~Tetris()
{
    for (size_t i = 0; i < figures.size(); i++)
    {
        delete figures[i];
    }
}

void Tetris::events() {

    float time = clock.getElapsedTime().asSeconds();
    clock.restart();
    timercount += time;

    auto e = std::make_shared<sf::Event>();
    while (window->pollEvent(*e)) {
        if (e->type == sf::Event::Closed) {
            window->close();
        }
        // Управление 
        if (e->type == sf::Event::KeyPressed) {
            if (e->key.code == sf::Keyboard::Up) {
                sound_rotateFigure.play();
                rotate = true;
            }
            else if (e->key.code == sf::Keyboard::Right) {
                sound_rotateFigure.play();
                ++dirx;
            }
            else if (e->key.code == sf::Keyboard::Left) {
                sound_rotateFigure.play();
                --dirx;
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        //sound_rotateFigure.play();
        delay = 0.05f;
    }
}

void Tetris::draw() {
    window->clear(sf::Color(50, 50, 50));

    window->draw(*background);
    window->draw(*backgroundTwo);

    for (std::size_t i{}; i < lines; ++i) {
        for (std::size_t j{}; j < cols; ++j) {
            if (area[i][j] != 0) {
                sprite->setTextureRect(sf::IntRect(area[i][j] * w, 0, w, w));
                sprite->setPosition(j * w, i * w);
                window->draw(*sprite);
            }
        }
    }

    for (std::size_t i{}; i < squares; ++i) {
        sprite->setTextureRect(sf::IntRect(color * w, 0, w, w));
        sprite->setPosition(z[i].getX() * w, z[i].getY() * w);
        window->draw(*sprite);
    }

    window->draw(*all_records[records::SCORE].first);
    window->draw(*all_records[records::Lines].first);

    int menuNum = 0;

    if (gameover) {
        window->draw(*all_records[records::GAMEOVER].first);
        sound_mainTheme.stop();
    }

    window->display();
}

void Tetris::run() {

    menu();

    sound_mainTheme.setLoop(true);
    sound_mainTheme.play();

    while (window->isOpen()) {
        events();
        if (!gameover) {
            changePosition();
            setRotate();
            moveToDown();
            setScore();
            resetValues();
        }
        draw();
    }
}

void Tetris::moveToDown() {
    if (timercount > delay) {                             //Заставляет фигуру смещаться вниз с течением времени
        for (std::size_t i{}; i < squares; ++i) {
            k[i] = z[i];
            ++z[i];
        }

        if (maxLimit()) {
            for (std::size_t i{}; i < squares; ++i) {    // Окрашивание фигуры
                area[k[i].getY()][k[i].getX()] = color;
            }

            color = std::rand() % shapes + 1;            // создание цвета для следующей фигуры

            std::uint32_t number = std::rand() % shapes; // создание фигуры
            figures[number]->changeZarray(z);
        }
        timercount = 0;
    }
}

void Tetris::setRotate() {  //Установка поворота 
    if (rotate) {
        Coords coords = z[1];
        for (std::size_t i{}; i < squares; ++i) {
            int x = z[i].getY() - coords.getY();
           int y = z[i].getX() - coords.getX();

           z[i].setX(coords.getX() - x);
           z[i].setY(coords.getY() + y);

        }

        if (maxLimit()) {
            for (std::size_t i{}; i < squares; ++i) {
                z[i] = k[i];
            }
        }
    }
}

void Tetris::loadResources()
{
    BulderText text_build;

    text_build.loadFont("./Assets/font/font2.ttf");
    text_build.setFont();
    text_build.setPosition(277, 200);
    text_build.setString("New Game");
    text_build.setCharSize(35);
    all_records.emplace_back(text_build.returnPair());


    text_build.loadFont("./Assets/font/font2.ttf");
    text_build.setFont();
    text_build.setPosition(313, 268);
    text_build.setString("Info");
    text_build.setCharSize(35);
    all_records.emplace_back(text_build.returnPair());


    text_build.loadFont("./Assets/font/font2.ttf");
    text_build.setFont();
    text_build.setPosition(313, 335);
    text_build.setString("Exit");
    text_build.setCharSize(35);
    all_records.emplace_back(text_build.returnPair());

    bg.loadFromFile("./Assets/image/background.png");
    background = std::make_shared<sf::Sprite>();
    background->setTexture(bg);

    bg2.loadFromFile("./Assets/image/background2.png");
    backgroundTwo = std::make_shared<sf::Sprite>();
    backgroundTwo->setTexture(bg2);
    backgroundTwo->setPosition(cols * w, 0);

    background1 = std::make_shared<sf::Sprite>();
    background1->setTexture(bg);
    background1->setPosition(0, 0);

    background2 = std::make_shared<sf::Sprite>();
    background2->setTexture(bg);
    background2->setPosition(340, 0);

    Texture1.loadFromFile("./Assets/image/information2.png");
    Tex1 = std::make_shared<sf::Sprite>();
    Tex1->setTexture(Texture1);
    Tex1->setPosition(374, 102);

    Texture2.loadFromFile("./Assets/image/move.png");
    Tex2 = std::make_shared<sf::Sprite>();
    Tex2->setTexture(Texture2);
    Tex2->setPosition(34, 136);

    sb_LP.loadFromFile("./Assets/sounds/LP.wav");
    sound_LP.setBuffer(sb_LP);

    tiles.loadFromFile("./Assets/image/tiles.png");
    sprite = std::make_shared<sf::Sprite>();
    sprite->setTexture(tiles);
    sprite->setTextureRect(sf::IntRect(0, 0, w, w));

    ico.loadFromFile("./Assets/image/icon.png");
    window->setIcon(64, 64, ico.getPixelsPtr());

    text_build.loadFont("./Assets/font/font.ttf");
    text_build.setFont();
    text_build.setPosition(434, 34);
    text_build.setString("SCORE: " + std::to_string(score));
    text_build.setCharSize(30);
    all_records.emplace_back(text_build.returnPair());

    text_build.loadFont("./Assets/font/font.ttf");
    text_build.setFont();
    text_build.setPosition(434, 102);
    text_build.setString("Lines: " + std::to_string(score));
    text_build.setCharSize(30);
    all_records.emplace_back(text_build.returnPair());

    text_build.loadFont("./Assets/font/font.ttf");
    text_build.setFont();
    text_build.setPosition(19, 300);
    text_build.setString("GAME OVER");
    text_build.setCharSize(50);
    text_build.setColor(sf::Color::Red);
    all_records.emplace_back(text_build.returnPair());

    sb_lineBoost.loadFromFile("./Assets/sounds/line++.wav");
    sound_lineBoost.setBuffer(sb_lineBoost);

    sb_gameOver.loadFromFile("./Assets/sounds/gameOver.wav");
    sound_gameOver.setBuffer(sb_gameOver);

    sb_rotateFigure.loadFromFile("./Assets/sounds/rotateFigure.wav");
    sound_rotateFigure.setBuffer(sb_rotateFigure);

    //sb_mainTheme.loadFromFile("./Assets/sounds/originalTet.wav");
    sb_mainTheme.loadFromFile("./Assets/sounds/Daive504.wav");
    //sb_mainTheme.loadFromFile("./Assets/sounds/Dora.wav");
    sound_mainTheme.setBuffer(sb_mainTheme);
}

void Tetris::resetValues() {
    dirx = 0;
    rotate = false;    
    delay = 0.3f - speed;
}

void Tetris::changePosition() {
    for (std::size_t i{}; i < squares; ++i) {
        k[i] = z[i];
        z[i].setX(z[i].getX() + dirx);
    }

    if (maxLimit()) {
        for (std::size_t i{}; i < squares; ++i) {
            z[i] = k[i];
        }
    }
}

bool Tetris::maxLimit() {                          // Не дает фигуре выйти за игровое поле
    for (std::size_t i{}; i < squares; ++i) {
        if (z[i].getX() < 0 ||
            z[i].getX() >= cols ||
            z[i].getY() >= lines ||
            area[z[i].getY()][z[i].getX()])
        {
            return true;
        }
    }
    return false;
}

void Tetris::setScore() {                       // Удалене сформ линии и присвоение очков
    std::uint32_t match = lines - 1;
    for (std::size_t i = match; i >= 1; --i) {
        std::uint32_t sum{};
        for (std::size_t j{}; j < cols; ++j) {
            if (area[i][j]) {
                if (i == 1) {
                    gameover = true;
                    sound_mainTheme.stop();
                    sound_gameOver.play();
                }
                ++sum;
            }
            area[match][j] = area[i][j];
        }
        if (sum < cols) {
            --match;
        }
        else {
            all_records[records::SCORE].first->setString("SCORE: " + std::to_string(++score * 5) + "00");
            all_records[records::Lines].first->setString("Lines: " + std::to_string(++Line)); 
            speed += 0.01f;
            sound_lineBoost.play();
        }
    }
}

void Tetris::menu()
{

    bool isMenu = 1;
    int menuNum = 0;

    while (isMenu)
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        all_records[records::NewGame].first->setFillColor(sf::Color::White);
        all_records[records::Info].first->setFillColor(sf::Color::White);
        all_records[records::Exit].first->setFillColor(sf::Color::White);

        menuNum = 0;
        window->clear(sf::Color(50, 50, 50));

        if (sf::IntRect(277.f, 200.f, 144.f, 40.f).contains(sf::Mouse::getPosition(*window))) { all_records[records::NewGame].first->setFillColor(sf::Color(200, 200, 30)); menuNum = 1; }
        if (sf::IntRect(277.f, 268.f, 144.f, 40.f).contains(sf::Mouse::getPosition(*window))) { all_records[records::Info].first->setFillColor(sf::Color(200, 200, 30)); menuNum = 2; }
        if (sf::IntRect(277.f, 335.f, 144.f, 40.f).contains(sf::Mouse::getPosition(*window))) { all_records[records::Exit].first->setFillColor(sf::Color(200, 200, 30)); menuNum = 3; }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (menuNum == 1) isMenu = false; //если нажали первую кнопку, то идем играть
            if (menuNum == 2) 
            {
                sound_LP.setLoop(true); sound_LP.play();
                window->draw(*background1);
                window->draw(*background2); 
                window->draw(*Tex1);
                window->draw(*Tex2);
                window->display();                 
                while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)); 
                sound_LP.stop();
            }
            if (menuNum == 3) { window->close(); isMenu = false; }
        }
        
        window->draw(*background1);
        window->draw(*background2);
        window->draw(*all_records[records::NewGame].first);
        window->draw(*all_records[records::Info].first);
        window->draw(*all_records[records::Exit].first);

        window->display();
    }
}