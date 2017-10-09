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
public class CalculatorClass {

    public CalculatorClass() {

    }
    private int firstNumber;
    private int secondNumber;
    private int result;

    public CalculatorClass(int firstNumber, int secondNumber) {
        this.firstNumber = firstNumber;
        this.secondNumber = secondNumber;
        this.result = 0;
    }

    public void addtwonumbers() {
        result = firstNumber + secondNumber;
    }

    void setFirstNumber(int firstNumber) {
        this.firstNumber = firstNumber;
    }

    void setSecondNumber(int secondNumber) {
        this.secondNumber = secondNumber;
    }

    public int getResult() {
        return this.result;
    }

}
