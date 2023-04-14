using System;
using System.Windows.Forms;


public class CSharpWindow:Form
{
    public static void Main()
    {
        Application.Run(new CSharpWindow());

        
    }

    public CSharpWindow()
    {
        Text = "My Csharp Window";
        BackColor = System.Drawing.Color.White;
        ResizeRedraw = true;

    }
}


