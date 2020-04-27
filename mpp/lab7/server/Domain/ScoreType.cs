using System;
using Triathlon;

namespace server.Domain
{
    public enum ScoreType
    {
        Cycling = 0,
        Running = 1,
        Swimming = 2,
    }

    public static class ScoreTypeUtils
    {
        public static ScoreTypeProto ToProto(ScoreType type)
        {
            return type switch
            {
                ScoreType.Cycling => ScoreTypeProto.Cycling,
                ScoreType.Running => ScoreTypeProto.Running,
                ScoreType.Swimming => ScoreTypeProto.Swimming,
                _ => throw new InvalidCastException()
            };
        }
    }
}
