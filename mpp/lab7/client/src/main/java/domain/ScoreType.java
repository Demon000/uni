package domain;

import grpc.triathlon.ScoreTypeProto;

public enum ScoreType {
    CYCLING,
    RUNNING,
    SWIMMING;

    public static ScoreType fromInteger(int value) {
        switch (value) {
            case 0:
                return CYCLING;
            case 1:
                return RUNNING;
            case 2:
                return SWIMMING;
            default:
                throw new IllegalArgumentException();
        }
    }

    public static ScoreType fromProto(ScoreTypeProto proto) {
        switch (proto) {
            case CYCLING:
                return CYCLING;
            case RUNNING:
                return RUNNING;
            case SWIMMING:
                return SWIMMING;
            case UNRECOGNIZED:
                throw new IllegalArgumentException();
        }

        return null;
    }
}
