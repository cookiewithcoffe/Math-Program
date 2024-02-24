#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
extern "C" {
    #include<conio.h>
}
#include "NewFeatures.hpp"
#include "Gui/Gui.hpp"

void any_func() {
    //func...
}

int main()
{
    int validPageonWindow = 0; // Ana ekran

    setlocale(LC_ALL, "Turkish");
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Pencere");

    gui::Menu menu(window);

    gui::Theme::loadFont("Resources/font.ttf");
    gui::Theme::loadTexture("Resources/texture-default.png");
    gui::Theme::textSize = 11;
    gui::Theme::click.textColor = hexConvert("#191B18");
    gui::Theme::click.textColorHover = hexConvert("#191B18");
    gui::Theme::click.textColorFocus = hexConvert("#000");
    gui::Theme::input.textColor = hexConvert("#000");
    gui::Theme::input.textColorHover = hexConvert("#000");
    gui::Theme::input.textColorFocus = hexConvert("#000");
    gui::Theme::input.textSelectionColor = hexConvert("#8791AD");
    gui::Theme::input.textPlaceholderColor = hexConvert("#8791AD");
    gui::Theme::windowBgColor = hexConvert("#729983");

    TestbookGui tbGui;

    //.choiceScreen(menu);

    std::vector<std::string> Lessons;
    std::vector<std::string> Tests;
    std::vector<std::string> Questions;

    std::cout << readLineFromFile("1sınıf.testbook", 193);

    std::string output_text;

    VoiceFeatures feature;
    TestBook book;

    bool a = false;//
    bool b = false;//
    bool c = false;
    bool ç = false;
    bool d = false;
    bool e = false;
    bool f = false;
    bool g = false;
    bool ğ = false;
    bool h = false;
    bool ı = false;
    bool i = false;
    bool İ = false;
    bool j = false;
    bool k = false;
    bool l = false;
    bool m = false;
    bool n = false;
    bool o = false;
    bool ö = false;
    bool p = false;
    bool r = false;
    bool s = false;
    bool ş = false;
    bool t = false;
    bool u = false;
    bool ü = false;
    bool v = false;
    bool y = false;
    bool z = false;
    int gh;
    while (window.isOpen())
    {
       
        sf::Event event;
        while (window.pollEvent(event))
        {
            menu.onEvent(event);
            if (event.type == sf::Event::Closed) {
                window.close();
                doonce(b, [&] {
                    system("del metin_dosyasi.txt output.wav output.mp3");
                    });
            }
        }

        doonce(a, [&] {
            runInBackground([&] {
                setlocale(LC_ALL, "turkish");
                feature.TTS("Kaçıncı sınıfsın?");
                feature.TTS("1.sınıf");
                feature.speechrecognation(RECOGNATION, output_text);
                output_text.erase(std::remove(output_text.begin(), output_text.end(), ' '), output_text.end());
                book.setBook(output_text + ".testbook");
                std::cout << "1. kısım";
                feature.TTS("Hangi dersin testini çözmek istiyorsun?");
                std::cout << "2. kısım";

                book.getLessons(Lessons);
                for (auto lesson : Lessons) {
                    feature.TTS(lesson);
                }
                feature.TTS("matematik");
                std::cout << "3. kısım";

                feature.speechrecognation(RECOGNATION, output_text);
                feature.TTS("Hangi testi çözmek istiyorsun?");
                std::cout << "4. kısım";
                output_text.erase(std::remove(output_text.begin(), output_text.end(), ' '), output_text.end());
                std::string lessonName = output_text;
                book.getTestsAboutLesson(Tests, lessonName);
                std::cout << "5. kısım";
                feature.TTS("bu derste " + std::to_string(Tests.size()) + "tane test var");
                for (auto tests : Tests) {
                    feature.TTS(tests);
                    std::cout << "6. kısım";
                }
                feature.TTS("test2.");
                std::cout << "7. kısım";
                feature.speechrecognation(RECOGNATION, output_text);
                output_text.erase(std::remove(output_text.begin(), output_text.end(), ' '), output_text.end());
                std::string testName = output_text;
                std::cout << testName;
                int questionNumber = 1;

                std::string correctAnswer;
                std::string question;
                std::string questionName = "Soru";
                
                std::cout << "8. kısım";
                stringiBuyukHarfeCevir(testName);
                book.getQuestions(Questions, testName);
                std::cout << "9. kısım";
                feature.TTS("bu testte " + std::to_string(Questions.size()) + "tane soru var");

                book.setBook("1sınıf.testbook");
                while (questionNumber <= Questions.size()) {
                    book.getQuestion("Soru" + std::to_string(questionNumber), testName, lessonName, question, correctAnswer);
                    write(converttoTurkishLetters(correctAnswer) + "\n");
                    write(converttoTurkishLetters(question) + "\n");
                    replaceCharacters(question, " ", "?");
                    replaceCharacters(question, "\n", "?");
                    feature.TTS(converttoTurkishLetters(question));
                    feature.TTS("Üçgen");
                    feature.speechrecognation(RECOGNATION, output_text);
                    std::string answer = capitalizeFirstLetter(output_text);
                    std::cout << answer;
                    std::cout << correctAnswer;
                    if (answer == correctAnswer) {
                        feature.TTS("Doğru");
                    }
                    else {
                        feature.TTS("Yanlış");
                    }

                    questionNumber = questionNumber + 1;
                }
                });
            });
        window.clear(gui::Theme::windowBgColor);
        window.draw(menu);
        window.display();
    }

    return 0;
}