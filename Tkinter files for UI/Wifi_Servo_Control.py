import tkinter as tk
import requests

ESP_IP = "http://192.168.137.171"

def update_angle(value,angle):
    try:
        url = f"{ESP_IP}/set?{angle}={value}"
        print(value)
        requests.get(url)
    except Exception as e:
        print(f"Error sending data: {e}")


root = tk.Tk()
root.title("Elephant Trunk control (Servo Control)")
root.geometry("450x500")
root.resizable(False, False)

# Servo 1
lab1 = tk.Label(root, text="Servo Angle")
lab1.pack(pady=(20, 5))  # add some spacing
slider1 = tk.Scale(root, from_=0, to=180, orient="horizontal", length=300,
                   command=lambda v: update_angle(v, "angle1"))
slider1.pack(pady=5)

# Servo 2
lab2 = tk.Label(root, text="Dummy1")
lab2.pack(pady=(20, 5))
slider2 = tk.Scale(root, from_=0, to=180, orient="horizontal", length=300,
                   command=lambda v: update_angle(v, "angle2"))
slider2.pack(pady=5)

# Servo 3
lab3 = tk.Label(root, text="Dummy2")
lab3.pack(pady=(20, 5))
slider3 = tk.Scale(root, from_=0, to=180, orient="horizontal", length=300,
                   command=lambda v: update_angle(v, "angle3"))
slider3.pack(pady=5)

root.mainloop()

