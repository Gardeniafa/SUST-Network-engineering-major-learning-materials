int main(){
    int array[10] = {0, 5, 8, 3, 1, 7, 9, 2, 4, 6};
    for (int i = 0; i < 10; i += 1){
        for (int j = i+1; j < 10; j += 1){
            if(array[i] > array[j]){
                int temp = array[j];
                array[j] = array[i];
                array[i] = temp;
            }
        }
    }
    return 0;
}