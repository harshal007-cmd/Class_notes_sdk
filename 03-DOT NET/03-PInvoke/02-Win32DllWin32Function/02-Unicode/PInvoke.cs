using System;
using System.Runtime.InteropServices;


public class PInvoke
{
    [DllImport("User32.dll",CharSet=CharSet.Unicode)]
    public static extern int MessageBoxW(int handle,String message,String caption,int type);

    public static void Main()
    {
        MessageBoxW(0, "This is Unicode message box", "Message.", 0);
       // Console.WriteLine("Cube of "+num1+" is "+num2);
    }
}


