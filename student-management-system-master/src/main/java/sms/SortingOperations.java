package sms;

public class SortingOperations {
    static {
        // Load the C++ shared library
        System.loadLibrary("NativeSorting");
    }

    // Declare a native method
    public native String[] sortStudents(String[] students);

    public static void main(String[] args) {
        SortingOperations operations = new SortingOperations();

        // Example student data
        String[] students = {"Alice,85", "Bob,95", "Charlie,75"};
        System.out.println("Before Sorting:");
        for (String student : students) {
            System.out.println(student);
        }

        // Call the native method
        String[] sortedStudents = operations.sortStudents(students);

        System.out.println("After Sorting:");
        for (String student : sortedStudents) {
            System.out.println(student);
        }
    }
}
