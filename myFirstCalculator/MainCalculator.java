/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package myFirstCalculator;

/**
 *
 * @author Student
 */
public class MainCalculator{
    public static void main(String[] args) {
        CalculatorClass myCalc = new CalculatorClass();
        myCalc.addtwonumbers();
        myCalc.setFirstNumber(4);
        myCalc.setSecondNumber(5);
        myCalc.getResult();
        // TODO code application logic here
    }
}
