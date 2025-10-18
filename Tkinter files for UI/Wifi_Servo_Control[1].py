import tkinter as tk
import requests

ESP_IP = "http://192.168.137.233"

def update_angle(value, angle):
    try:
        url = f"{ESP_IP}/set?{angle}={value}"
        print(value, angle)
        requests.get(url)
    except Exception as e:
        print(f"Error sending data: {e}")


root = tk.Tk()
root.title("Elephant Trunk Control (Servo Control)")
root.geometry("400x250")
root.resizable(False, False)

# Values for cycling
values = [0, 90, 180]
index1, index2, index3 = 0, 0, 0

def cycle_angle1(servo):
    global index1
    value = values[index1]
    update_angle(value, servo)
    index1 = (index1 + 1) % len(values)

def cycle_angle2(servo):
    global index2
    value = values[index2]
    update_angle(value, servo)
    index2 = (index2 + 1) % len(values)

def cycle_angle3(servo):
    global index3
    value = values[index3]
    update_angle(value, servo)
    index3 = (index3 + 1) % len(values)

# Servo 1
tk.Label(root, text="Servo 1").grid(row=0, column=0, padx=20, pady=15, sticky="w")
tk.Button(root, text="Move", width=10, command=lambda: cycle_angle1("angle1")).grid(row=0, column=1, padx=10)

# Servo 2
tk.Label(root, text="Servo 2").grid(row=1, column=0, padx=20, pady=15, sticky="w")
tk.Button(root, text="Move", width=10, command=lambda: cycle_angle2("angle2")).grid(row=1, column=1, padx=10)

# Servo 3
tk.Label(root, text="Servo 3").grid(row=2, column=0, padx=20, pady=15, sticky="w")
tk.Button(root, text="Move", width=10, command=lambda: cycle_angle3("angle3")).grid(row=2, column=1, padx=10)

root.mainloop()
