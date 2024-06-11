module Vivid.Test

class Vec3

    float x,y,z;

    func Vec3()

        x=0;
        y=0;
        z=0;

    end 

    func Set(float sx,float sy,float sz)

        x = sx;
        y = sy;
        z = sz;
        

    end 

    func Times(Vec3 r)

        Vec3 res = new Vec3();

        res.x = x * r.x;
        res.y = y * r.y;
        res.z = z * r.z;

        return res;

    end

end 


class TestClass

  
    func TestClass() 

        Vec3 v1 = new Vec3();
        Vec3 v2 = new Vec3();   

        v1.Set(10,20,30);
        v2.Set(10,20,30);

        Vec3 v3 = v1 * v2 * v1 * v1;

        debug("V1");
        debug(v3.x);
        debug(v3.y);
        debug(v3.z);

    end 

end 


