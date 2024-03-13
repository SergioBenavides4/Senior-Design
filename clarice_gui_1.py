import tkinter as tk 
from tkinter import ttk
from tkinter import messagebox
from tkinter import simpledialog
import socket
import threading
import json
import time
# Format for the data encoding 
Format = 'utf-8'

# GUI Class
class gui:
    def __init__(self,root) :
        # Initialize the variables and other things
        self.root =root 
        self.record = False     #Condition to check if the server is recording inputs
        self.script=[]  #The recorded script being sent 
        self.control_list={     # Dictionary to match with the bytes being sent to Arduino
        'Up':'U',
        'Down':'D',
        'Left':'L',
        'Right':'R',
        'q':'q',
        'space':'b',
        'Return': 'N',
        'o':'O',
        'p':'P',
        'z':'Z',
        'x':'X',
        'c':'C'}
        self.presetScript = ["0","1","2","3","4","5","6","7","8","9"]

        # place holder for the dictionary so we can write it to the json file
        self.dictScript = {
            "0":["L","R"],
            "1":["U","D"], 
            "2":["U","L"],
            "3":["U","R"],
            "4":["U","D"],
            "5":["L","U"],
            "6":["D","U"],
            "7":["U","R"],
            "8":["R","L"],
            "9":["R","D"]
           }

        # The server IP and PORT for server
        self.IP = '192.168.1.2'
        self.PORT = 8080

        # # Make the server socket and bind it witht he IP and PORT
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.bind((self.IP,self.PORT))
        self.conn = None

        # # Listen for any connections coming in 
        self.server.listen()
        print('Listening for Connection...')

        # # Start a thread for the server so it doesn't hinder the rest of the functions
        threading.Thread(target = self.servacp).start()

        # Layout of the GUI
        self.root.title('Animatronic Control')
        self.root.geometry('800x600')
        self.controlsLabel = tk.Label(root,text = "Use the arrow keys to control the animatronic",font=("Helvetica", 18))
        self.controlsLabel.pack()
        self.recordingLabel = tk.Label(root,text = 'Recording', font=("Helvetica", 18))
        self.recordingLabel.pack(pady= 10)
        self.buttonEchoLabel = tk.Label(root,text = "Button Pressed was: ",font = ("helvetica",20))
        self.buttonEchoLabel.pack( pady= 20)

        # Inputs
        self.root.bind('<KeyPress>',self.send_key)
        self.root.bind('s',self.savsenScript)

    # * Functions *
        
    # The server and client communication
    def servacp(self):
        while (1):
            self.conn , self.addr = self.server.accept()
            print(f'Connection has been established with {self.addr}')
            print(f'Active Connections: {threading.active_count()-1}')
            data = self.conn.recv(1024).decode(Format)
            print(f'Response from the Arduino is {data}')
            if data == 'q':
                break
        self.conn.close()
        print('Arduino has disconnected...')
    
    # Recognizing the key pressed, key echo, and sending commands to arduino
    def send_key(self,event):
        # Get the key represented with the key press
        key = event.keysym

        # Echo the button back to the GUI
        self.buttonEchoLabel.config(text = 'Button Pressed: '+ key)

        # Check if it's recording, if yes, append them to the script, else send individualy 
        if self.record:
            if key in self.control_list:
                self.script.append(self.control_list[key])
            elif key =='r':
                self.toggleRecord()
            else:
                pass
        else:
            if key in self.control_list:
                sendcom = self.control_list[key]
                self.conn.send(sendcom.encode(Format))
            elif key in self.presetScript:
                with open("scriptList.json", "r") as p:
                    fop = json.load(p)
                
                for acting in fop[key]:
                    self.conn.send(acting.encode(Format))
                    time.sleep(1)

            elif key == 'r':
                self.toggleRecord()



    # Change the recording state and indicate on the GUI 
    def toggleRecord(self):
        # Change the recording state
        self.record = not self.record

        # Change colors
        if self.record:
            self.recordingLabel.config(fg = 'red')
            print('recording')
        else:
            self.recordingLabel.config(fg = 'white')
            print('not recording')
        
        # When recording is done send the script
        if not self.record:
            self.sendScript()

    # Sends the script to Arduino
    def sendScript(self):
        # Prompts the user if they want to save and saves their answer 
        saver = tk.messagebox.askyesno(message = "Do you wanna save the recorded inputs?")

        # If they did not want to save they would send the script normally
        # If they did want to save it would run the sensavScript function
        if not saver:
            for act in self.script:
                self.conn.send(act.encode(Format))
                time.sleep(2)
                self.script = []
        else:
            self.savsenScript()
            pass
    
    # Saves the script for the available slots in "script.py"
    def savsenScript(self, event = None):
        # If there is a recorded script go through
        if self.script:
            # Prompts the user if they want to save their script from 0-9
            index= simpledialog.askstring("Input","Enter the number key 0-9 you want to save:")

            # Changes the dictionary for the script
            self.dictScript[index] = self.script

            # Overwrites/adds script into the file
            with open("scriptList.json", "w") as f:
                json.dump(self.dictScript,f)

            # Notifies them that the script has been changed
            tk.messagebox.showinfo(message = "Script has been saved.") 
            # Reset the script array/ clear the inputs
            self.script = []
        else:
            # If there is nothing to save there would be a popup
            tk.messagebox.showerror(message = "There is nothing to save.")
        pass


# Main function to run 
if __name__ == '__main__':
    root = tk.Tk()
    GUI = gui(root)
    root.mainloop()
