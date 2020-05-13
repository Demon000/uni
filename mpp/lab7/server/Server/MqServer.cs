using Google.Protobuf;
using RabbitMQ.Client;
using server.Domain;

namespace server.Server
{
    public class MqServer : Service.IServiceObserver
    {
        private IConnection mqConnection;
        private IModel mqChannel;
        private readonly string _host;
        private readonly int _port;

        public MqServer(string host, int port)
        {
            _host = host;
            _port = port;
        }

        private const string ExchangeName = "scores";
        public void Start()
        {
            var factory = new ConnectionFactory { HostName = _host, Port = _port };
            mqConnection = factory.CreateConnection();
            mqChannel = mqConnection.CreateModel();
            mqChannel.ExchangeDeclare(ExchangeName, ExchangeType.Fanout);
        }

        public void Stop()
        {
            mqChannel.Close();
            mqConnection.Close();
        }

        public void OnSetScore(Score score)
        {
            var data = score.ToProto().ToByteArray();
            mqChannel.BasicPublish(ExchangeName, "", null, data);
        }
    }
}
