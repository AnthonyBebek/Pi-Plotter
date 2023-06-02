import PySimpleGUI as psg
import os
import sys
print(sys.getrecursionlimit())

layout = [
   [psg.Text('Select a file',font=('Arial Bold', 20), expand_x=True, justification='center')],
   [psg.Input(enable_events=True, key='-IN-',font=('Arial Bold', 12),expand_x=True), psg.FileBrowse()],
   [psg.Button('Convert', size = (11,2))]
   
   
]



window = psg.Window('Plotter', layout)
while True:
   event, values = window.read()
   if event == psg.WIN_CLOSED or event == 'Exit':
      break
   if event == 'Convert':
      print(values['-IN-'])
      
   
window.close()
