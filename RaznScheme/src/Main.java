import gauss.Algorithm;
import gauss.LinearSystem;
import gauss.MyEquation;

import java.io.FileWriter;
import java.io.IOException;

public class Main {
    private static int EQUATIONS_NUMBER;
    private static int VARIABLES_NUMBER;

    public static void main(String[] args){
        VARIABLES_NUMBER = Integer.parseInt(args[0]);
        EQUATIONS_NUMBER = Integer.parseInt(args[0]);

        LinearSystem<Float, MyEquation> list = generateSystem();
        printSystem(list);
        int i, j;
        Algorithm<Float, MyEquation> alg = new Algorithm<>(list);
        try{
            alg.calculate();
        }
        catch (NullPointerException | ArithmeticException ex){
            System.out.println(ex.getMessage());
            System.exit(0);
        }
        Float[] y = new Float[EQUATIONS_NUMBER];
        for(i = list.size() - 1; i >= 0; i--){
            Float sum = 0.0f;
            for(j = list.size() - 1; j > i; j--){
                sum += list.itemAt(i, j)*y[j];
            }
            y[i] = (list.itemAt(i, list.size()) - sum) / list.itemAt(i,j);
        }
        printSystem(list);
        printVector(y);
    }

    public static LinearSystem<Float, MyEquation> generateSystem(){
        LinearSystem<Float, MyEquation> list = new LinearSystem<>();
        int eqNumber;
        for(eqNumber = 1; eqNumber <= EQUATIONS_NUMBER; eqNumber++){
            MyEquation eq = new MyEquation();
            if(eqNumber == 1){
                float x1 = (float)1/(EQUATIONS_NUMBER+1);
                eq.generateFirstEq(VARIABLES_NUMBER + 1, f(x1));
            }
            else if(eqNumber == EQUATIONS_NUMBER){
                float xN = (float)(EQUATIONS_NUMBER)/(EQUATIONS_NUMBER+1);
                eq.generateLastEq(VARIABLES_NUMBER + 1, f(xN));
            }
            else {
                float xi = (float)(eqNumber)/(EQUATIONS_NUMBER+1);
                eq.generateDefault(VARIABLES_NUMBER + 1, f(xi), eqNumber);
            }
            list.push(eq);
        }
        return list;
    }

    public static void printSystem(LinearSystem<Float, MyEquation> system){
        for(int i = 0 ; i < system.size(); i++){
            MyEquation temp = system.get(i);
            StringBuilder s = new StringBuilder();
            for(int j = 0; j < temp.size(); j++){
                s.append(String.format("%f; %s", system.itemAt(i, j), "\t"));
            }
            System.out.println(s);
        }
        System.out.println();
    }

    public static void printVector(Float [] y){
        StringBuilder s = new StringBuilder();
        try(FileWriter writer = new FileWriter("results.csv")) {
            for (int i = 0; i < y.length; i++) {
                writer.append(String.format("%f;\n", y[i]));
                s.append(String.format("y[%d] = %f; ", i, y[i]));
            }
            System.out.println(s);
            writer.flush();
        }
        catch (IOException ex){
            System.out.println(ex.getMessage());
        }
    }

    public static float f(float x){
        return -3*x*x + x*x*x;
    }

}
