package repository;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

@Retention(RetentionPolicy.RUNTIME)
public @interface DatabaseField {
    String name();
    String type();
    boolean notNull() default false;
    boolean primaryKey() default false;
    boolean unique() default false;
    String foreignKey() default "";
}
