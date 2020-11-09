package gauss;

import java.util.ArrayList;
import java.util.List;
import java.util.ListIterator;

public class MyEquation implements Gauss<Float, MyEquation>{
    private final List<Float> equation = new ArrayList<>();
    public List<Float> getEquation(){
        return equation;
    }

    public void generateDefault(int size, float fi, int eqInd){
        float h = (1.0f/(float)(size));
        this.equation.clear();
        for(int i = 1; i <= size; i++){
            if(i == size){
                this.equation.add(fi);
            }
            else if(i == eqInd-1 || i == eqInd + 1){
                this.equation.add(-(1/(h*h)));
            }
            else if(i == eqInd){
                this.equation.add((2/(h*h)) + 1);
            }
            else{
                this.equation.add(0.0f);
            }
        }
    }

    public void generateFirstEq(int size, float fi){
        float h = (1.0f/(float)(size));
        this.equation.clear();
        for(int i = 1; i <= size; i++){
            if(i == 1){
                this.equation.add((2/(h*h)) + 1);
            }
            else if(i == 2){
                this.equation.add(-(1/(h*h)));
            }
            else if(i == size){
                this.equation.add(fi);
            }
            else {
                this.equation.add(0.0f);
            }
        }
    }

    public void generateLastEq(int size, float fi){
        float h = (1.0f/(float)(size));
        this.equation.clear();
        for(int i = 1; i <= size; i++){
            if(i == size - 1){
                this.equation.add((2/(h*h)) + 1);
            }
            else if(i == size - 2){
                this.equation.add(-(1/(h*h)));
            }
            else if(i == size){
                this.equation.add(fi + (1/(h*h)));
            }
            else {
                this.equation.add(0.0f);
            }
        }
    }

    @Override
    public void addEquation(MyEquation item) {
        ListIterator<Float> i = equation.listIterator();
        ListIterator<Float> j = item.getEquation().listIterator();
        while (i.hasNext() && j.hasNext()) {
            Float a = i.next();
            Float b = j.next();
            i.set(a + b);
        }
    }

    @Override
    public void mul(Float coefficient) {
        for(ListIterator<Float> i = equation.listIterator(); i.hasNext();){
            Float next = i.next();
            i.set(next * coefficient);
        }
    }

    @Override
    public Float findCoefficient(Float a, Float b) {
        if(a == 0.0f) return 1.0f;
        return -b/a;
    }

    @Override
    public Float at(int index) {
        return equation.get(index);
    }

    @Override
    public int size() {
        return equation.size();
    }
}
