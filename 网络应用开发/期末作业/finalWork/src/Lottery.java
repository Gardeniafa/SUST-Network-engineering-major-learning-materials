import java.util.Arrays;
import java.util.Random;

public class Lottery {
    public static String getAllLottery() {
        boolean[] canBeChosen = new boolean[23];
        Arrays.fill(canBeChosen, true);
        int theNumberOfSelected = 0;
        int randomIndex;
        Random random = new Random();
        int[] chosenNumOf_5 = new int[5];
        while(true) {
            randomIndex = random.nextInt(22) + 1;
            if(canBeChosen[randomIndex]) {
                canBeChosen[randomIndex] = false;
                chosenNumOf_5[theNumberOfSelected++] = randomIndex;
            }
            else
                continue;
            if(theNumberOfSelected == 5)
                break;
        }
        StringBuilder retString = new StringBuilder("22选5: ");
        for (int i = 0; i < theNumberOfSelected; i++) {
            retString.append(chosenNumOf_5[i]).append(" ");
        }
        canBeChosen = new boolean[34];
        Arrays.fill(canBeChosen, true);
        theNumberOfSelected = 0;
        int[] chosenNumOf_7 = new int[7];
        while(true) {
            randomIndex = random.nextInt(33) + 1;
            if(canBeChosen[randomIndex]) {
                canBeChosen[randomIndex] = false;
                chosenNumOf_7[theNumberOfSelected++] = randomIndex;
            }
            else
                continue;
            if(theNumberOfSelected == 7)
                break;
        }
        retString.append("\n33选7: ");
        for (int i = 0; i < theNumberOfSelected; i++) {
            retString.append(chosenNumOf_7[i]).append(" ");
        }
        canBeChosen = new boolean[34];
        Arrays.fill(canBeChosen, true);
        theNumberOfSelected = 0;
        int[] chosenNumOfRedBlue = new int[6];
        while(true) {
            randomIndex = random.nextInt(33) + 1;
            if(canBeChosen[randomIndex]) {
                canBeChosen[randomIndex] = false;
                chosenNumOfRedBlue[theNumberOfSelected++] = randomIndex;
            }
            else
                continue;
            if(theNumberOfSelected == 6)
                break;
        }
        retString.append("\n红色球: ");
        for (int i = 0; i < theNumberOfSelected; i++) {
            retString.append(chosenNumOfRedBlue[i]).append(" ");
        }
        retString.append("  蓝色球: ");
        randomIndex = random.nextInt(16) + 1;
        retString.append(randomIndex).append(" ");
        return retString.toString();
    }
}

class demo_06{
    public static void main(String[] args) {
        System.out.println(Lottery.getAllLottery());
    }
}
