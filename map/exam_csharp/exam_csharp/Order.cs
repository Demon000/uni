using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace exam_csharp
{
    class Order
    {
        public int RoomNumber { get; set; }
        public String ProductName { get; set; }
        public float ProductPrice { get; set; }
        public DateTime Time { get; set; }

        public Order(int RoomNumber, String ProductName, float ProductPrice, DateTime Time)
        {
            this.RoomNumber = RoomNumber;
            this.ProductName = ProductName;
            this.ProductPrice = ProductPrice;
            this.Time = Time;
        }

        public override string ToString()
        {
            return
                $"Room number: {RoomNumber}, Product name: {ProductName}, Product price: {ProductPrice}, Time: {Time}";
        }
    }
}
