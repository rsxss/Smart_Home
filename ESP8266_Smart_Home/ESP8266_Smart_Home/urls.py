"""ESP8266_Smart_Home URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/2.0/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path
from Sensor import  views as sensor

urlpatterns = [
    path('admin/', admin.site.urls),
    path('index/', sensor.sensor_home, name="sensor_home"),
    path('RFID_log/', sensor.RFID_log, name="RFID_log"),
    path('Setting/', sensor.setting, name="setting"),
]
