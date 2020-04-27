package utils;

import io.grpc.*;

public class GrpcHeaderCopy implements ClientInterceptor {
    private final Metadata.Key<String> headerKey;
    private String headerValue;

    public GrpcHeaderCopy(String name) {
        headerKey = Metadata.Key.of(name, Metadata.ASCII_STRING_MARSHALLER);
    }

    @Override
    public <ReqT, RespT> ClientCall<ReqT, RespT> interceptCall(MethodDescriptor<ReqT, RespT> method,
                                                               CallOptions callOptions, Channel next) {
        return new ForwardingClientCall.SimpleForwardingClientCall<>(next.newCall(method, callOptions)) {
            @Override
            public void start(Listener<RespT> responseListener, Metadata headers) {
                if (headerValue != null) {
                    headers.put(headerKey, headerValue);
                }
                super.start(new ForwardingClientCallListener.SimpleForwardingClientCallListener<>(responseListener) {
                    @Override
                    public void onHeaders(Metadata headers) {
                        if (headers.containsKey(headerKey)) {
                            headerValue = headers.get(headerKey);
                        }
                        super.onHeaders(headers);
                    }
                }, headers);
            }
        };
    }
}
