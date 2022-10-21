public class test {

    public static int f(int[] arr, int[] goal) {
        int rowSz = 3;
        int manhattanDistanceSum = 0;
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] != goal[i])
                manhattanDistanceSum += (Math.abs(arr[i] / rowSz - i / rowSz)
                        + Math.abs(arr[i] % rowSz - i % rowSz));
        }
        return manhattanDistanceSum;
    }

    public static int sum(int x, int y) {
        return x + y;
    }

    public static int manhattan(int board[][]) {
        int distance = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 0) {
                    distance += sum(Math.abs((i - 1) % 3 - i % 3), Math.abs((j - 1)));
                }
            }
        }
        return distance;
    }

    public static void main(String[] args) {

        // int test[] = {
        // 1, 2, 3,
        // 0, 8, 4,
        // 7, 6, 5
        // };
        // int goal[] = {
        // 1, 2, 3,
        // 8, 0, 4,
        // 7, 6, 5
        // };

        int _2D_test[][] = {
                { 1, 2, 3 },
                { 0, 8, 4 },
                { 7, 6, 5 }
        };

        int a = manhattan(_2D_test);
        System.out.println(a);

    }
}