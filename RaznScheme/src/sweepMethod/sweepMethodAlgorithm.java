package sweepMethod;

import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Locale;

public class sweepMethodAlgorithm {
    public static void main(String[] args) throws FileNotFoundException {

        final int N = Integer.parseInt(args[0]);
        final double h = 1.0f / (N + 1);
        final double h2 = h * h;

        double[] A = new double[N + 1];
        double[] B = new double[N + 1];
        double[] C = new double[N + 1];
        double[] F = new double[N + 1];

        C[1] = (2 / h2) + 1;
        B[1] = 1 / h2;
        F[1] = f(h);

        for (int i = 2; i <= N - 1; i++) {
            double xi = i * h;
            A[i] = 1 / h2;
            C[i] = (2 / h2) + 1;
            B[i] = 1 / h2;
            F[i] = f(xi);
        }

        double xn = N * h;
        A[N] = 1 / h2;
        C[N] = (2 / h2) + 1;
        F[N] = f(xn) + 1 / h2;

        double[] alpha = new double[N + 1];
        double[] beta = new double[N + 1];

        // right stroke
        alpha[1] = B[1] / C[1];
        beta[1] = F[1] / C[1];
        for (int i = 2; i <= N - 1; i++) {
            double denominator = C[i] - A[i] * alpha[i - 1];
            alpha[i] = B[i] / denominator;
            beta[i] = (F[i] + A[i] * beta[i - 1]) / denominator;
        }

        double[] y = new double[N + 1];

        // back stroke
        y[N] = (F[N] + A[N] * beta[N - 1]) / (C[N] - A[N] * alpha[N - 1]);
        for (int i = N - 1; i >= 1; i--) {
            y[i] = alpha[i] * y[i + 1] + beta[i];
        }

        // output
        PrintWriter pw = new PrintWriter("output.txt");
        for (int i = 1; i <= N; i++) {
            pw.printf(Locale.US, "y[%d] = %f\n", i, y[i]);
        }
        pw.flush();
        pw.close();

        try (FileWriter writer = new FileWriter("results.csv")) {
            for (int i = 1; i <= N; i++) {
                writer.append(String.format("%f;\n", y[i]));
            }
            writer.flush();
        } catch (IOException ex) {
            System.out.println(ex.getMessage());
        }

    }

    public static double f(double x){
        return -3*x*x + x*x*x;
    }
}
