from django.shortcuts import render
from firebase import firebase
# Create your views here.
firebase = firebase.FirebaseApplication('https://smarthomev01-626ae.firebaseio.com')
LED_status = False

def sensor_home(request):
    if request.method == "POST":
        #result = firebase.get('/test', 'GPIO')
        #print(result)
        global LED_status
        LED_status = not LED_status
        firebase.put('/Sensor', 'LED_status', LED_status)
        Sensor_val = firebase.get('/Sensor', 'Sensor_val')
        context={'LED_status': LED_status,
                 'Sensor_val': Sensor_val,
                 }
        return render(request,"home.html",context)
    else:
        return render(request,"home.html", {'LED_status':LED_status})