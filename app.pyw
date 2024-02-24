import sys
import speech_recognition as sr
from gtts import gTTS
from pydub import AudioSegment
import os

def speech_to_text(audio_file_path):
    recognizer = sr.Recognizer()

    with sr.AudioFile(audio_file_path) as source:
        audio_data = recognizer.record(source)

    # Dosyayı yazma modunda aç
    with open('metin_dosyasi.txt', 'w') as dosya:
        # Dosyaya yazma işlemi
        try:
            # Google Web Speech API'yi kullanarak konuşmayı metne çevir
            text = recognizer.recognize_google(audio_data, language="tr")
            dosya.write("Metin: {}".format(text))
        except sr.UnknownValueError:
            dosya.write("Konuşma anlaşılamadı.")
        except sr.RequestError as e:
            dosya.write("Google Web Speech API'ye ulaşılamadı; {0}".format(e))
    
    

def text_to_speech(text, lang='tr'):
    # gTTS nesnesini oluştur
    tts = gTTS(text=text, lang=lang, slow=False)

    # Ses dosyasını oluştur (MP3 formatında)
    tts.save("output.mp3")

    # MP3 dosyasını WAV formatına dönüştür
    sound = AudioSegment.from_mp3("output.mp3")
    sound.export("output.wav", format="wav")

def main():
    job = sys.argv[1]
    string = sys.argv[2]

    if job == "tts":
        text_to_speech(string)
    elif job == "stt":
        speech_to_text(string)
    else:
        print("Geçersiz işlem: {}".format(job))

if __name__ == "__main__":
    main()
