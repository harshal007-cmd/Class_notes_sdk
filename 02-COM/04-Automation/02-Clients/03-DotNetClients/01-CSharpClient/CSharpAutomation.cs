using System;
using System.Runtime.InteropServices;
using AutomationServerTypeLibForDotNet;

public class CSharpAutomation
{
	public static void Main()
	{
		//code
		CMyMathClass objCMyMathClass = new CMyMathClass();
		IMyMath objIMymath=(IMyMath)(objCMyMathClass);

		int num1, num2, sum, sub;
		num1 = 165;
		num2 = 135;
		sum = objIMymath.SumOfTwoIntergers(num1, num2);
		Console.WriteLine("Sum of "+num1+" and "+num2+" is "+sum);
		sub = objIMymath.SubtractionOfTwoIntergers(num1, num2);
		Console.WriteLine("Subtraction of " + num1 + " and " + num2 + " is " + sub);
	}

}
