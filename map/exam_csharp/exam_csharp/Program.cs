using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;

namespace exam_csharp
{
    class Program
    {
        static void Main(string[] args)
        {
            String[] lines = System.IO.File.ReadAllLines("Comenzi.txt");
            List<Order> orders = new List<Order>();
            for(int i = 0; i < lines.Length; i++)
            {
                String[] parts = lines[i].Split('\t');
                int roomNumber = Convert.ToInt32(parts[0]);
                String productName = parts[1];
                float productPrice = Convert.ToSingle(parts[2]);
                DateTime time = DateTime.ParseExact(parts[3], "dd/MM/yyyy HH:mm", CultureInfo.InvariantCulture);
                Order order = new Order(roomNumber, productName, productPrice, time);
                orders.Add(order);
            }

            foreach (var order in orders)
            {
                Console.WriteLine(order);
            }

            var results = (
                from firstOrder in orders
                from secondOrder in orders
                let distance = Math.Abs((firstOrder.Time - secondOrder.Time).TotalHours)
                where firstOrder != secondOrder && firstOrder.RoomNumber == secondOrder.RoomNumber
                orderby distance
                select firstOrder.RoomNumber).ToList();

            foreach (var result in results)
            {
                Console.WriteLine(result);
            }
        }
    }
}
