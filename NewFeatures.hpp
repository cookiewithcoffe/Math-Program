#pragma once

#ifndef NEWFEATURES_HPP
#define NEWFEATURES_HPP

#define LISTEN 1
#define RECOGNATION 0

#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <cctype>
#include <sstream>
#include <locale>

#include "Gui/Gui.hpp"

sf::Color hexConvert(const std::string& hexcolor)
{
	sf::Color color = sf::Color::Black;
	if (hexcolor.size() == 7) // #ffffff
	{
		color.r = strtoul(hexcolor.substr(1, 2).c_str(), NULL, 16);
		color.g = strtoul(hexcolor.substr(3, 2).c_str(), NULL, 16);
		color.b = strtoul(hexcolor.substr(5, 2).c_str(), NULL, 16);
	}
	else if (hexcolor.size() == 4) // #fff
	{
		color.r = strtoul(hexcolor.substr(1, 1).c_str(), NULL, 16) * 17;
		color.g = strtoul(hexcolor.substr(2, 1).c_str(), NULL, 16) * 17;
		color.b = strtoul(hexcolor.substr(3, 1).c_str(), NULL, 16) * 17;
	}
	return color;
}

std::string capitalizeFirstLetter(const std::string& input) {
	setlocale(LC_ALL, "turkish");
	if (input.empty()) {
		return input; // Boş bir string ise işlem yapmaya gerek yok.
	}

	std::string result = input;
	result[0] = std::toupper(result[0]); // İlk harfi büyük yap.

	return result;
}

void replaceCharacters(std::string& text, const std::string& target, const std::string& replacement) {
	setlocale(LC_ALL, "turkish");
	size_t found = text.find(target);
	while (found != std::string::npos) {
		text.replace(found, target.length(), replacement);
		found = text.find(target);
	}
}

std::string belirliSatirlariYazdir(const std::string& dosyaAdi, int baslangicSatir, int bitisSatir) {
	setlocale(LC_ALL, "turkish");
	std::ifstream dosya(dosyaAdi);

	if (dosya.is_open()) {
		std::ostringstream stream;

		std::string satir;
		int satirNumarasi = 1;

		while (std::getline(dosya, satir)) {
			if (satirNumarasi >= baslangicSatir && satirNumarasi <= bitisSatir) {
				stream << satir << '\n';
			}

			if (satirNumarasi == bitisSatir) {
				break;
			}

			satirNumarasi++;
		}

		dosya.close();
		return stream.str();
	}
	else {
		return "Dosya acilamadi: " + dosyaAdi;
	}
}

std::string dosyaOku(std::string dosyaNerede) {
	setlocale(LC_ALL, "Turkish");
	std::string dosyaAdi = dosyaNerede;

	// ifstream nesnesini oluştur ve dosyayı aç
	std::ifstream dosya(dosyaAdi);

	// Dosyanın başarıyla açılıp açılmadığını kontrol et
	if (!dosya.is_open()) {
		std::cerr << "Dosya acilamadi: " << dosyaAdi << std::endl;
	}

	// Dosyadan okuma işlemi
	std::string satir;
	while (std::getline(dosya, satir)) {
		// "Metin:" kelimesini içeren satırı bul
		size_t pozisyon = satir.find("Metin: ");
		if (pozisyon != std::string::npos) {
			return satir.substr(pozisyon + 7);
		}
	}

	// Dosyayı kapat
	dosya.close();

	// "Metin:" bulunamadıysa boş bir string döndür
	return "";
}


std::string turkishToEnglish(const std::string& text) {
	setlocale(LC_ALL, "turkish");
	std::string result = text;

	// Türkçe karakterleri İngilizce karakterlere dönüştür
	for (size_t i = 0; i < result.length(); ++i) {
		switch (result[i]) {
		case 'ç':
			result[i] = 'c';
			break;
		case 'ğ':
			result[i] = 'g';
			break;
		case 'ı':
			result[i] = 'i';
			break;
		case 'ö':
			result[i] = 'o';
			break;
		case 'ş':
			result[i] = 's';
			break;
		case 'ü':
			result[i] = 'u';
			break;
		case 'Ç':
			result[i] = 'C';
			break;
		case 'Ğ':
			result[i] = 'G';
			break;
		case 'İ':
			result[i] = 'I';
			break;
		case 'Ö':
			result[i] = 'O';
			break;
		case 'Ş':
			result[i] = 'S';
			break;
		case 'Ü':
			result[i] = 'U';
			break;
		default:
			break;
		}
	}

	return result;
}

std::string converttoTurkishLetters(const std::string& text) {
	setlocale(LC_ALL, "turkish");
	std::string result = text;

	// Türkçe karakterleri İngilizce karakterlere dönüştür
	replaceCharacters(result, "Ã§", "ç");
	replaceCharacters(result, "ÅY", "ş");
	replaceCharacters(result, "Ä±", "ı");
	replaceCharacters(result, "Ã¼", "ü");
	replaceCharacters(result, "Ã¶", "ö");
	replaceCharacters(result, "Ã┼", "Ç");
	replaceCharacters(result, "Å?", "Ş");
	replaceCharacters(result, "Ä°", "İ");
	replaceCharacters(result, "Ã-", "Ö");
	replaceCharacters(result, "Ão", "Ü");
	replaceCharacters(result, "Ä?", "Ğ");
	replaceCharacters(result, "ÄY", "ğ");

	return result;
}

void write(std::string wordstowrite) {
	setlocale(LC_ALL, "turkish");
	std::cout << wordstowrite;
}

template <typename Func, typename... Args>
void doonce(bool& isDoonce, Func callback, Args&&... args) {
	if (!isDoonce) {
		callback(std::forward<Args>(args)...);
		isDoonce = true;
	}
	else {
		//std::cout << "it did once";
	}
}

void stringiBuyukHarfeCevir(std::string& str) {
	setlocale(LC_ALL, "turkish");
	for (char& c : str) {
		c = std::toupper(c);
	}
}

template <typename Func, typename... Args>
void runInBackground(Func worktodo, Args&&... args) {
	std::thread(worktodo).detach();
}

template <typename Func, typename... Args>
void check(bool condition, Func worktodo, Args&&... args) {
	if (condition) {
		worktodo(std::forward<Args>(args)...);
	}
}

class VoiceFeatures {
public:
	void TTS(std::string sentence) {
		setlocale(LC_ALL, "turkish");
		sentence.erase(std::remove(sentence.begin(), sentence.end(), ' '), sentence.end());
		std::string command = "python app.pyw tts " + sentence;
		const char* command_word = command.c_str();
		system(command_word);

		buffer.loadFromFile("output.wav");

		sf::Time duration = buffer.getDuration();

		wordstosay.openFromFile("output.wav");
		wordstosay.play();
		sf::sleep(sf::seconds(float(duration.asSeconds())));
	}

	void speechrecognation(bool recognation, std::string& output_text) {
		setlocale(LC_ALL, "turkish");
		if (recognation && isRuninbefore == 0) {
			if (recorder.isAvailable()) {
				recorder.start(44100);
				isRuninbefore = 1;
			}
		}
		else {
			isRuninbefore = 0;

			system("python app.pyw stt output.wav");

			output_text = dosyaOku("metin_dosyasi.txt");
			write(output_text + "\n");
		}
	}


private:
	//speak fonksiyonu için
	sf::SoundBuffer buffer;
	sf::Music wordstosay;
	//listen fonksiyonu için
	sf::SoundBufferRecorder recorder;
	sf::SoundBuffer recordBuffer;
	bool isRuninbefore = false;
};

void printLinesBetween(std::ifstream& file, int startLine, int endLine, std::string& data) {
	std::string line;
	int currentLine = 1;

	while (std::getline(file, line)) {
		if (currentLine >= startLine && currentLine <= endLine) {
			line = data;
		}

		if (currentLine > endLine) {
			break; // Bitiş satırından sonrasına geçmeyi durdur
		}

		++currentLine;
	}
}

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string readLineFromFile(const string& filename, int lineNumber) {
	ifstream file(filename);
	string line;
	int currentLine = 0;

	if (file.is_open()) {
		while (getline(file, line)) {
			currentLine++;
			if (currentLine == lineNumber) {
				file.close();
				return line;
			}
		}
		file.close();
	}
	else {
		cerr << "Unable to open file: " << filename << endl;
	}

	return "Didn't find"; // If line is not found or file cannot be opened
}


class TestbookGui{
public:
	template <typename Func, typename... Args>
	void choiceScreen(gui::Menu& menu, Func callback, Args&&... args) {
		gui::Label* askLabel = new gui::Label("Ne yapmak istiyorsun?");
		menu.add(askLabel);
		askLabel->setTextSize(36);
		
		gui::Button* solveTest_btn = new gui::Button("Test Çöz");
		menu.add(solveTest_btn);
		solveTest_btn->setCallback(callback);

		gui::Button* exit_btn = new gui::Button(L"Çık");
		menu.add(exit_btn);

		exit_btn->setPosition(500, 300);
		solveTest_btn->setPosition(200, 300);
		askLabel->setPosition(200, 50);
	}

private:
	
};

class TestBook {
public:

	/*TestBook(std::string Name) {
		TestBookFile.open(Name);
		if (!TestBookFile.is_open()) {
			std::cerr << "Dosya acilamadi: " << Name << std::endl;
			return;
		}
	}*/

	void setBook(std::string Name) {
		setlocale(LC_ALL, "turkish");
		TestBookFile.open(Name);
		BookName = Name;
		if (!TestBookFile.is_open()) {
			std::cerr << "Dosya acilamadi: " << Name << std::endl;
			return;
		}
		else {
		}
	}

	void getLessons(std::vector<std::string>& Lessons) {
		setlocale(LC_ALL, "turkish");
		TestBookFile.clear();
		TestBookFile.seekg(0, std::ios::beg);
		std::string line;
		while (std::getline(TestBookFile, line)) {
			size_t lessonline = line.find("Lesson: ");
			if (lessonline != std::string::npos) {
				Lessons.push_back(line.substr(lessonline + 8));
			}
		}
	}

	void getTestsAboutLesson(std::vector<std::string>& Tests, std::string& lessonName) {
		setlocale(LC_ALL, "turkish");
		TestBookFile.clear();  // Reset the file, start reading from the beginning
		TestBookFile.seekg(0, std::ios::beg);

		std::string line;
		int lineNumber = 2;  // To keep track of the line number

		// Find the starting line of the specified lesson
		while (std::getline(TestBookFile, line)) {
			size_t lessonLine = line.find("Lesson: ");
			lessonName.erase(std::remove(lessonName.begin(), lessonName.end(), ' '), lessonName.end());
			if (lessonLine != std::string::npos && line.substr(lessonLine + 8) == lessonName) {
				// Found the line where the specified lesson starts
				break;
			}
			++lineNumber;
		}

		// If the lesson is not found, display an error message
		if (TestBookFile.eof()) {
			std::cerr << "Ders bulunamadi: " << lessonName << std::endl;
			return;
		}

		int endOfLessonLineNumber = -1;  // To store the line number of "________end of lesson part____________"

		// Find the tests for the specified lesson
		while (std::getline(TestBookFile, line)) {
			size_t endOfLessonLine = line.find("________end of lesson part____________");
			size_t testLine = line.find("TEST");

			if (testLine != std::string::npos) {
				Tests.push_back(line);
			}

			if (endOfLessonLine != std::string::npos) {
				// Found the line where "________end of lesson part____________" occurs
				endOfLessonLineNumber = lineNumber;
				break;
			}

			++lineNumber;
		}

		// Display the line number of "________end of lesson part____________"
		/*if (endOfLessonLineNumber != -1) {
			std::cout << "Line number of '________end of lesson part____________': " << endOfLessonLineNumber << std::endl;
		}*/
	}

	void getQuestions(std::vector<std::string>& Questions, const std::string& TestNumber) {
		setlocale(LC_ALL, "turkish");
		TestBookFile.clear();  // Reset the file, start reading from the beginning
		TestBookFile.seekg(0, std::ios::beg);

		std::string line;
		int lineNumber = 2;  // To keep track of the line number

		// Find the starting line of the specified lesson
		while (std::getline(TestBookFile, line)) {
			size_t lessonLine = line.find("TEST");
			if (lessonLine != std::string::npos && line.substr(lessonLine) == TestNumber) {
				// Found the line where the specified lesson starts
				break;
			}
			++lineNumber;
		}

		// If the lesson is not found, display an error message
		if (TestBookFile.eof()) {
			std::cerr << "Test bulunamadi: " << TestNumber << std::endl;
			return;
		}

		int endOfTestLineNumber = -1;  // To store the line number of "----------end of test------------"

		// Find the tests for the specified lesson
		while (std::getline(TestBookFile, line)) {
			size_t endOfTestLine = line.find("----------end of test------------");
			size_t questionLine = line.find("Soru");

			if (questionLine != std::string::npos) {
				Questions.push_back(line);
			}

			if (endOfTestLine != std::string::npos) {
				// Found the line where "----------end of test------------" occurs
				endOfTestLineNumber = lineNumber;
				break;
			}

			++lineNumber;
		}

		// Display the line number of "----------end of test------------"
		if (endOfTestLineNumber != -1) {
			std::cout << "Line number of '----------end of test------------': " << endOfTestLineNumber << std::endl;
		}
	}

	void getQuestion(std::string questionName, std::string testName, std::string lessonName,std::string& questionContent,std::string& correctAnswer) {
		setlocale(LC_ALL, "turkish");
		TestBookFile.clear();  // Reset the file, start reading from the beginning
		TestBookFile.seekg(0, std::ios::beg);

		std::string line;
		int lineNumber = 2;  // To keep track of the line number

		while (std::getline(TestBookFile, line)) {
			size_t lessonLine = line.find("Lesson: ");
			lessonName.erase(std::remove(lessonName.begin(), lessonName.end(), ' '), lessonName.end());
			if (lessonLine != std::string::npos && line.substr(lessonLine + 8) == lessonName) {
				// Found the line where the specified lesson starts
				break;
			}
			++lineNumber;
		}

		// Find the starting line of the specified lesson
		while (std::getline(TestBookFile, line)) {
			size_t lessonLine = line.find("TEST");
			if (lessonLine != std::string::npos && line.substr(lessonLine) == testName) {
				// Found the line where the specified lesson starts
				break;
			}
			++lineNumber;
		}

		// If the lesson is not found, display an error message
		if (TestBookFile.eof()) {
			std::cerr << "Test bulunamadi: " << testName << std::endl;
			return;
		}

		int endOfTestLineNumber = 1;  // To store the line number of "----------end of test------------"
		int CorrectAnswerLineNumber = 1;
		int questionLineNumber = 1;

		// Find the tests for the specified lesson
		while (std::getline(TestBookFile, line)) {
			
			size_t questionLine = line.find(questionName);

			if (questionLine != std::string::npos) {
				questionLineNumber = lineNumber;
				break;
			}

			++lineNumber;
		}

		while (std::getline(TestBookFile, line)) {
			size_t CorrectAnswerLine = line.find("CorrectAnswer=");

			if (CorrectAnswerLine != std::string::npos) {
				CorrectAnswerLineNumber = lineNumber;
				correctAnswer = line.substr(CorrectAnswerLine + 14);
				break;
			}
			++lineNumber;
		}

		// Display the line number of "----------end of test------------"
		if (CorrectAnswerLineNumber != -1) {
			std::cout << "Line number of 'CorrectAnswer=': " << CorrectAnswerLineNumber << std::endl;
		}

		std::cout << questionLineNumber
			<< "\n"
			<< CorrectAnswerLineNumber
			<< "\n";

		questionContent = belirliSatirlariYazdir(BookName, questionLineNumber+1, CorrectAnswerLineNumber+1);
	}

private:
	std::ifstream TestBookFile;
	std::string BookName;
};

#endif