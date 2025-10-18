from tkinter import *
import requests
import time

pending_request_list=[]
ESP_IP = "http://192.168.137.233"

def pending_requests(value, angle, delay=1):
    pending_request_list.append([value, angle, delay])

def display_clicked(value, angle):
    message=angle+" "+str(value)+"\u00B0"
    display_list.insert(0, message)

def button_clicked(value, angle):
    pending_requests(value,angle)
    display_clicked(value, angle)

def dynamic_angle(entry_name, angle):
    entered_value=int((entry_name.get()).strip())
    display_clicked(entered_value, angle)
    pending_requests(entered_value, angle)
    entry_name.delete(0, END)

def update_delay(delay_name):
    delay_value=float(delay_name.get().strip())
    pending_request_list[-1][2]=delay_value
    delay_name.delete(0, END)

def execute():
    for value, angle, delay in pending_request_list:
        pass
        try:
            url = f"{ESP_IP}/set?{angle}={value}"
            print(f"{value}\u00B0->{angle}->{delay}s")
            requests.get(url)
        except Exception as e:
            print(f"Error sending data: {e}")
        time.sleep(delay)

    display_list.delete(0, END)
    pending_request_list.clear()

window=Tk()
window.geometry("600x300")
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

Label(window, text="Other Angle: ").grid(row=0, column=4, padx=10, pady=20)
entry1=Entry(window, width=7)
entry1.grid(row=0, column=5, padx=10, pady=20)
Button(window, text="\u2714", width=2, height=1, command=lambda: dynamic_angle(entry1, "Servo 1")).grid(row=0, column=6)

Label(window, text="Other Angle: ").grid(row=1, column=4, padx=10, pady=20)
entry2=Entry(window, width=7)
entry2.grid(row=1, column=5, padx=10, pady=20)
Button(window, text="\u2714", width=1, height=1, command=lambda: dynamic_angle(entry2,"Servo 2")).grid(row=1, column=6)

Label(window, text="Other Angle: ").grid(row=2, column=4, padx=10, pady=20)
entry3=Entry(window, width=7)
entry3.grid(row=2, column=5, padx=10, pady=20)
Button(window, text="\u2714", width=1, height=1, command=lambda: dynamic_angle(entry3,"Servo 3")).grid(row=2, column=6)

# Label(window, text="Set Delay(s): ").grid(row=0, column=7, padx=10, pady=20)
# delay1=Entry(window, width=4)
# delay1.grid(row=0, column=8, padx=10, pady=20)
# Button(window, text="\u2714", width=2, height=1, command=lambda: update_delay(delay1)).grid(row=0, column=9)

Label(window, text="Set Delay(s): ").grid(row=3, column=4, padx=10, pady=20)
delay2=Entry(window, width=7)
delay2.grid(row=3, column=5, padx=10, pady=20)
Button(window, text="\u2714", width=2, height=1, command=lambda: update_delay(delay2)).grid(row=3, column=6)

# Label(window, text="Set Delay(s): ").grid(row=2, column=7, padx=10, pady=20)
# delay3=Entry(window, width=4)
# delay3.grid(row=2, column=8, padx=10, pady=20)
# Button(window, text="\u2714", width=2, height=1, command=lambda: update_delay(delay3)).grid(row=2, column=9)


Button(window, text="Execute", width=20, background="Red", foreground="Yellow", command=execute).grid(row=3, column=2, columnspan=2, padx=10, pady=20)

window.mainloop()





