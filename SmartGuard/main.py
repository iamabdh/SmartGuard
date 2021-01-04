from firebase import firebase
from kivy.app import App
from kivy.uix.label import Label
from kivy.clock import Clock
from kivy.core.audio import SoundLoader



class SensorData (Label):
    def update (self, *args):
        status = firebase.FirebaseApplication('https:REALTIME_DATABASE_URL', None).get('/DATA', None)
        self.font_size = ('30sp')
        if status == 1:
            self.text = "Thief Spotted!!"
            self.color= 1, 0, 0, 1
            sound = SoundLoader.load('beep.wav').play()
        else :
            self.color = 1, 1, 1, 1
            self.text = "EveryThing Look Fine So Far .."

class MyApp (App):
    def build(self):
        latestUpdate = SensorData()
        Clock.schedule_interval(latestUpdate.update, 1) #replace here
        return latestUpdate

if __name__ == '__main__':
    app = MyApp()
    app.run()
