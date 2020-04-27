package service;

import io.grpc.ConnectivityState;
import io.grpc.ManagedChannel;

public class ChannelStateListener {
    private final StateListener listener;
    private ManagedChannel channel;

    public interface StateListener {
        void onStateChanged(ConnectivityState status);
    }

    public ChannelStateListener(StateListener listener) {
        this.listener = listener;
    }

    public void setChannel(ManagedChannel channel) {
        this.channel = channel;

        restart();
    }

    private void restart() {
        ConnectivityState currentState = channel.getState(false);
        channel.notifyWhenStateChanged(currentState, () -> {
            ConnectivityState newState = channel.getState(false);
            if (currentState != newState) {
                System.out.println(currentState + " -> " + newState);
                listener.onStateChanged(newState);
            }

            restart();
        });
    }
}
