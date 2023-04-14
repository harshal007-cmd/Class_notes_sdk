using System;
using System.Runtime.InteropServices;


public class PInvoke
{
    [DllImport("User32.dll")]
    public static extern int MessageBoxA(int handle,String message,String caption,int type);

    public static void Main()
    {
        MessageBoxA(0, "This is ANSI message box", "Message.", 0);
       // Console.WriteLine("Cube of "+num1+" is "+num2);
    }
}

