package service;

import com.rabbitmq.client.*;
import domain.Score;
import grpc.triathlon.ScoreProto;

import java.io.IOException;
import java.util.concurrent.TimeoutException;

public class MqService extends Observable implements ICanStart {
    public static String SCORE_SET_EVENT = "SCORE_SET_EVENT";
    private static String EXCHANGE_NAME = "scores";

    private final ConnectionFactory factory;
    private Connection connection;
    private Channel channel;

    public MqService(String mqServerAddress, int mqServerPort) {
        factory = new ConnectionFactory();
        factory.setHost(mqServerAddress);
        factory.setPort(mqServerPort);
    }

    protected boolean isStarted() {
        return connection != null && connection.isOpen() && channel != null && channel.isOpen();
    }

    @Override
    public void start() throws CanStartError {
        if (isStarted()) {
            return;
        }

        try {
            connection = factory.newConnection();
            channel = connection.createChannel();
            channel.exchangeDeclare(EXCHANGE_NAME, BuiltinExchangeType.FANOUT);
            String queueName = channel.queueDeclare().getQueue();
            channel.queueBind(queueName, EXCHANGE_NAME, "");
            channel.basicConsume(queueName, true, deliverCallback, consumerTag -> { });
        } catch (IOException | TimeoutException e) {
            throw new CanStartError(e);
        }
    }

    DeliverCallback deliverCallback = (consumerTag, message) -> {
        ScoreProto proto = ScoreProto.parseFrom(message.getBody());
        Score score = Score.fromProto(proto);
        observersSendEvent(SCORE_SET_EVENT, score);
    };

    @Override
    public void stop() throws CanStartError {
        if (!isStarted()) {
            return;
        }

        try {
            channel.close();
            connection.close();
        } catch (IOException | TimeoutException e) {
            throw new CanStartError(e);
        }
    }
}
