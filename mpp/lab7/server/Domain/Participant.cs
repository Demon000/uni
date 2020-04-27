using Triathlon;

namespace server.Domain
{
    public class Participant
    {
        public int Id { get; set; }
        public string Name { get; }

        public Participant(int id, string name)
        {
            Id = id;
            Name = name;
        }

        public Participant(string name)
                : this(0, name)
        { }

        public override string ToString()
        {
            return $"Participant{{Id={Id}, Name={Name}}}";
        }

        public ParticipantProto ToProto()
        {
            return new ParticipantProto { Id = Id, Name = Name};
        }
    }
}
