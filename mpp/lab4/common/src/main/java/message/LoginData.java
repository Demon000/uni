package message;

import java.io.Serializable;

public class LoginData implements Serializable {
    private final String name;
    private final String password;

    public LoginData(String name, String password) {
        this.name = name;
        this.password = password;
    }

    public String getName() {
        return name;
    }

    public String getPassword() {
        return password;
    }
}
