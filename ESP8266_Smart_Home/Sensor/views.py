from typing import re

from django.shortcuts import render
from firebase import firebase
# Create your views here.
firebase = firebase.FirebaseApplication('https://smarthomev01-626ae.firebaseio.com')

def sensor_home(request):
    if request.method != "POST":
        #result = firebase.get('/test', 'GPIO')
        #print(result)
        '''global LED_status
        LED_status = not LED_status
        firebase.put('/Sensor', 'LED_status', LED_status)'''
        fb_sensor_obj = firebase.get('/Sensor',None)
        print (fb_sensor_obj)
        gas = fb_sensor_obj['GAS']
        rain = fb_sensor_obj['Rain']
        temp_i = fb_sensor_obj['Temp_I']
        temp_o = fb_sensor_obj['Temp_O']
        context={'GAS': gas,
                 'Rain': rain,
                 'Temp_I': temp_i,
                 'Temp_O': temp_o,
                 }
        return render(request,"home.html",context)
    else:
        return render(request,"home.html")

def RFID_log(request):
    fb_RFID_obj = firebase.get('/Log',None)
    context = {'RFID_log':fb_RFID_obj,
               }
    print(fb_RFID_obj)
    return render(request,"RFID.html",context)

def setting(request):
    if (request.method == "POST" and request.POST.get("ON","")):
        rs = 1
        firebase.put("/Setting","Rain_status",rs)
    elif (request.method == "POST" and request.POST.get("OFF","")):
        rs = 0
        firebase.put("/Setting","Rain_status",rs)
    elif (request.method == "POST" and request.POST.get("OK","")):
        gs = float(request.POST.get("gs"))
        firebase.put("/Setting","GAS_alert",gs)
    fb_setting_obj = firebase.get('/Setting',None)
    GAS_alert = fb_setting_obj['GAS_alert']
    Rain_status = fb_setting_obj['Rain_status']
    print(Rain_status)
    if (Rain_status == 1):
        Rain_status = "ON"

    elif (Rain_status == 0):
        Rain_status = "OFF"

    else: Rain_status = "ERROR"
    context = {'GAS_alert':GAS_alert,
               'Rain_status':Rain_status,
               }
    return render(request,"setting.html",context)