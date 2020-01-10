using System;
using System.Xml.Serialization;

namespace lab8.domain
{
    public class Student<TId> : Entity<TId>
        where TId : class
    {
        public string Name { get; set;  }

        public Student() : base()
        {}
        
        public Student(TId studentId, string name)
            : base(studentId)
        {
            Name = name;
        }
    }
}
