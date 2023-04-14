using System;
using System.Windows.Forms;
using System.Drawing;

public class CSharpWindow:Form
{
    public static void Main()
    {
        Application.Run(new CSharpWindow());
       
    }

    public CSharpWindow()
    {
        Icon = new Icon("MyIcon.ico");
        Text = "My Csharp Window";
        BackColor = Color.Black;
        ResizeRedraw = true;
        Width = 800;
        Height = 600;

        this.KeyDown += new KeyEventHandler(MyKeyDown);
        this.MouseDown += new MouseEventHandler(MyMouseDown);

    }
    //WM_Paint ahe he, pea is Wparam and Lparam
    protected override void OnPaint(PaintEventArgs pea)
    {
        Graphics grfx=pea.Graphics;

        StringFormat strfmt = new StringFormat();
        strfmt.Alignment = StringAlignment.Center;//horizontal center
        strfmt.LineAlignment = StringAlignment.Center;//vertical center

        grfx.DrawString("Hello World!!!",
                        Font,
                        new SolidBrush(Color.Green),
                        ClientRectangle,
                        strfmt);
    }

    void MyKeyDown(object Sender, KeyEventArgs e)
    {
        MessageBox.Show("A key is pressed!!!");
    }

    void MyMouseDown(object Sender,MouseEventArgs e)
    {
        MessageBox.Show("A mouse is clicked");
    }
}



