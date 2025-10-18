from tkinter import *
import requests
import time

pending_request_list=[]
ESP_IP = "http://192.168.137.233"

def pending_requests(value, angle):
    pending_request_list.append((value, angle))

def display_clicked(value, angle):
    message=angle+" "+str(value)+"\u00B0"
    display_list.insert(0, message)

def button_clicked(value, angle):
    pending_requests(value,angle)
    display_clicked(value, angle)

def execute():
    for value, angle in pending_request_list:
        try:
            url = f"{ESP_IP}/set?{angle}={value}"
            print(f"{value}\u00B0->{angle}")
            requests.get(url)
        except Exception as e:
            print(f"Error sending data: {e}")
        time.sleep(1)

    display_list.delete(0, END)
    pending_request_list.clear()

window=Tk()
window.geometry("400x300")
window.title("Trunk Controller")
window.resizable(False, False)

display_list=Listbox(window, height=5, width=10)
display_list.grid(row=3, column=1, columnspan=1, padx=10, pady=20)
Label(window, text="Movements:").grid(row=3, column=0, padx=10, pady=20)

Label(window, text="Servo 1").grid(row=0, column=0, padx=10, pady=20)
Button(window, text="0\u00B0", width=5, height=2, command=lambda :button_clicked(0, "Servo 1")).grid(row=0, column=1, padx=10)
Button(window, text="90\u00B0", width=5, height=2, command=lambda :button_clicked(90, "Servo 1")).grid(row=0, column=2, padx=10)
Button(window, text="180\u00B0", width=5, height=2, command=lambda :button_clicked(180, "Servo 1")).grid(row=0, column=3, padx=10)

Label(window, text="Servo 2").grid(row=1, column=0, padx=10, pady=20)
Button(window, text="0\u00B0", width=5, height=2, command=lambda :button_clicked(0, "Servo 2")).grid(row=1, column=1, padx=5)
Button(window, text="90\u00B0", width=5, height=2, command=lambda :button_clicked(90, "Servo 2")).grid(row=1, column=2, padx=5)
Button(window, text="180\u00B0", width=5, height=2, command=lambda :button_clicked(180, "Servo 2")).grid(row=1, column=3, padx=5)

Label(window, text="Servo 3").grid(row=2, column=0, padx=10, pady=20)
Button(window, text="0\u00B0", width=5, height=2, command=lambda :button_clicked(0, "Servo 3")).grid(row=2, column=1, padx=5)
Button(window, text="90\u00B0", width=5, height=2, command=lambda :button_clicked(90, "Servo 3")).grid(row=2, column=2, padx=5)
Button(window, text="180\u00B0", width=5, height=2, command=lambda :button_clicked(180, "Servo 3")).grid(row=2, column=3, padx=5)

Button(window, text="Execute", width=20, background="Red", foreground="Yellow", command=execute).grid(row=3, column=2, columnspan=2, padx=10, pady=20)

window.mainloop()

