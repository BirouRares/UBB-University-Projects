using System;
using System.Collections.Generic;

public class SortingAlgorithms<T> where T : IComparable<T>
{
    public enum SortingAlgorithm
    {
        BubbleSort,
        MergeSort,
        GnomeSort
    }

    public void Sort(List<T> list, SortingAlgorithm algorithm)
    {
        switch (algorithm)
        {
            case SortingAlgorithm.BubbleSort:
                BubbleSort(list);
                break;
            case SortingAlgorithm.MergeSort:
                MergeSort(list);
                break;
            case SortingAlgorithm.GnomeSort:
                GnomeSort(list);
                break;
            default:
                throw new ArgumentException("Invalid sorting algorithm specified.");
        }
    }

    private void BubbleSort(List<T> list)
    {
        bool swapped;
        int n = list.Count;
        do
        {
            swapped = false;
            for (int i = 1; i < n; i++)
            {
                if (list[i - 1].CompareTo(list[i]) > 0)
                {
                    Swap(list, i - 1, i);
                    swapped = true;
                }
            }
            n--;
        } while (swapped);
    }

    private void MergeSort(List<T> list)
    {
        if (list.Count <= 1)
            return;

        int middle = list.Count / 2;
        List<T> left = new List<T>();
        List<T> right = new List<T>();

        for (int i = 0; i < middle; i++)
            left.Add(list[i]);
        for (int i = middle; i < list.Count; i++)
            right.Add(list[i]);

        MergeSort(left);
        MergeSort(right);
        Merge(list, left, right);
    }

    private void Merge(List<T> list, List<T> left, List<T> right)
    {
        int leftIndex = 0;
        int rightIndex = 0;
        int mergeIndex = 0;

        while (leftIndex < left.Count && rightIndex < right.Count)
        {
            if (left[leftIndex].CompareTo(right[rightIndex]) <= 0)
            {
                list[mergeIndex] = left[leftIndex];
                leftIndex++;
            }
            else
            {
                list[mergeIndex] = right[rightIndex];
                rightIndex++;
            }
            mergeIndex++;
        }

        while (leftIndex < left.Count)
        {
            list[mergeIndex] = left[leftIndex];
            leftIndex++;
            mergeIndex++;
        }

        while (rightIndex < right.Count)
        {
            list[mergeIndex] = right[rightIndex];
            rightIndex++;
            mergeIndex++;
        }
    }

    private void GnomeSort(List<T> list)
    {
        int index = 0;
        while (index < list.Count)
        {
            if (index == 0 || list[index - 1].CompareTo(list[index]) <= 0)
                index++;
            else
            {
                Swap(list, index - 1, index);
                index--;
            }
        }
    }

    private void Swap(List<T> list, int i, int j)
    {
        T temp = list[i];
        list[i] = list[j];
        list[j] = temp;
    }
}

class Program
{
    static void Main(string[] args)
    {
        Console.WriteLine("Enter elements of the list separated by spaces:");
        string input = Console.ReadLine();
        List<string> elements = new List<string>(input.Split(' '));

        Console.WriteLine("Choose a sorting algorithm:");
        Console.WriteLine("1. Bubble Sort");
        Console.WriteLine("2. Merge Sort");
        Console.WriteLine("3. Gnome Sort");
        Console.Write("Enter the number corresponding to your choice: ");

        if (int.TryParse(Console.ReadLine(), out int choice))
        {
            SortingAlgorithms<string> sorter = new SortingAlgorithms<string>();
            SortingAlgorithms<string>.SortingAlgorithm algorithm = SortingAlgorithms<string>.SortingAlgorithm.BubbleSort;

            switch (choice)
            {
                case 1:
                    algorithm = SortingAlgorithms<string>.SortingAlgorithm.BubbleSort;
                    break;
                case 2:
                    algorithm = SortingAlgorithms<string>.SortingAlgorithm.MergeSort;
                    break;
                case 3:
                    algorithm = SortingAlgorithms<string>.SortingAlgorithm.GnomeSort;
                    break;
                default:

                    Console.WriteLine("Invalid choice. Using Bubble Sort.");
                    Console.ReadLine();
                    break;
            }

            sorter.Sort(elements, algorithm);

            Console.WriteLine("\n\nSorted list:");
            

            foreach (var element in elements)
            {
                Console.Write(element + " ");
            }
            Console.WriteLine();
            Console.ReadLine();
        }
        else
        {
            Console.WriteLine("Invalid input.");
            Console.ReadLine();
        }
    }
}
