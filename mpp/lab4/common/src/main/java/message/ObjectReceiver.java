package message;

public interface ObjectReceiver {
    default void onReceive(Object object) {}
}
