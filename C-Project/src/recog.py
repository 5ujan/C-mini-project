import speech_recognition as sr
r = sr.Recognizer()
with sr.Microphone() as source:
    r.pause_threshold=0.5  
    audio = r.listen(source)
try:
    print("listening")
    query = r.recognize_google(audio)
    print(query)        
    
except Exception as e:
        
    print("cannot recognize your voice, can you say that again")

#pip install SpeechRecognition
#pip install requests