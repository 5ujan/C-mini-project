import requests
weather_key='ada316e43c6f22450f8acbf5838bbfd5'
url='https://api.openweathermap.org/data/2.5/forecast'
params = {'APPID': weather_key, 'q':'kathmandu','units':'imperial'}
response = requests.get(url,params=params)
weather=response.json()
#text_src(weather['name'])
#text_src(weather['weather'][0]['description'])
tempinf=weather['list'][0]['main']['temp']
tempinc=(tempinf-32)*5/9
rtemp=str(tempinc)
rtempinc=rtemp[:4]
description=weather['list'][0]['weather'][0]['description']
print(f"the temperature is {rtempinc} degree celsius with {description}")