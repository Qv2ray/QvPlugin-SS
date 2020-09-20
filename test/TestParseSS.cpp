#include "core/Serializer.hpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

SCENARIO("Test Parse Shadowsocks url", "[ParseSSUrl]")
{
    GIVEN("A shadowsocks server object")
    {
        SSSerializer ss;
        ShadowSocksServerObject s;
        QString err;
        QString alias = "ssurl1";
        WHEN("the url without padding")
        {
            auto c = ss.DeserializeOutbound("ss://YmYtY2ZiOnRlc3RAMTkyLjE2OC4xMDAuMTo4ODg4", &alias, &err);
            s = ShadowSocksServerObject::fromJson(c.second);
            REQUIRE(s.address.toStdString() == "192.168.100.1");
            REQUIRE(s.port == 8888);
            REQUIRE(s.password.toStdString() == "test");
            REQUIRE(s.method.toStdString() == "bf-cfb");
        }
        WHEN("the url with padding")
        {
            auto c = ss.DeserializeOutbound("ss://YmYtY2ZiOnRlc3RAMTkyLjE2OC4xLjE6ODM4OA==", &alias, &err);
            s = ShadowSocksServerObject::fromJson(c.second);
            REQUIRE(s.address.toStdString() == "192.168.1.1");
            REQUIRE(s.port == 8388);
            REQUIRE(s.password.toStdString() == "test");
            REQUIRE(s.method.toStdString() == "bf-cfb");
        }
        WHEN("the url with remarks")
        {
            auto c = ss.DeserializeOutbound("ss://YmYtY2ZiOnRlc3RAMTkyLjE2OC4xMDAuMTo4ODg4#example-server", &alias, &err);
            s = ShadowSocksServerObject::fromJson(c.second);
            REQUIRE(s.address.toStdString() == "192.168.100.1");
            REQUIRE(s.port == 8888);
            REQUIRE(s.password.toStdString() == "test");
            REQUIRE(s.method.toStdString() == "bf-cfb");
        }
        WHEN("the url with remarks and padding")
        {
            auto c = ss.DeserializeOutbound("ss://YmYtY2ZiOnRlc3RAMTkyLjE2OC4xLjE6ODM4OA==#example-server", &alias, &err);
            s = ShadowSocksServerObject::fromJson(c.second);
            REQUIRE(s.address.toStdString() == "192.168.1.1");
            REQUIRE(s.port == 8388);
            REQUIRE(s.password.toStdString() == "test");
            REQUIRE(s.method.toStdString() == "bf-cfb");
        }
        WHEN("the url with sip003 plugin")
        {
            auto c = ss.DeserializeOutbound("ss://YmYtY2ZiOnRlc3Q@192.168.100.1:8888/?plugin=obfs-local%3bobfs%3dhttp%3bobfs-host%3dgoogle.com",
                                            &alias, &err);
            s = ShadowSocksServerObject::fromJson(c.second);
            REQUIRE(s.address.toStdString() == "192.168.100.1");
            REQUIRE(s.port == 8888);
            REQUIRE(s.password.toStdString() == "test");
            REQUIRE(s.method.toStdString() == "bf-cfb");
            REQUIRE(s.plugin.toStdString() == "obfs-local");
            REQUIRE(s.plugin_options.toStdString() == "obfs=http;obfs-host=google.com");
        }
        WHEN("another url with sip003 plugin")
        {
            auto c = ss.DeserializeOutbound("ss://YmYtY2ZiOnRlc3Q@192.168.1.1:8388/?plugin=obfs-local%3bobfs%3dhttp%3bobfs-host%3dgoogle.com",
                                            &alias, &err);
            s = ShadowSocksServerObject::fromJson(c.second);
            REQUIRE(s.address.toStdString() == "192.168.1.1");
            REQUIRE(s.port == 8388);
            REQUIRE(s.password.toStdString() == "test");
            REQUIRE(s.method.toStdString() == "bf-cfb");
            REQUIRE(s.plugin.toStdString() == "obfs-local");
            REQUIRE(s.plugin_options.toStdString() == "obfs=http;obfs-host=google.com");
        }
        WHEN("the url with sip003 plugin and remarks")
        {
            auto c = ss.DeserializeOutbound(
                "ss://YmYtY2ZiOnRlc3Q@192.168.100.1:8888/?plugin=obfs-local%3bobfs%3dhttp%3bobfs-host%3dgoogle.com#example-server", &alias,
                &err);
            s = ShadowSocksServerObject::fromJson(c.second);
            REQUIRE(s.address.toStdString() == "192.168.100.1");
            REQUIRE(s.port == 8888);
            REQUIRE(s.password.toStdString() == "test");
            REQUIRE(s.method.toStdString() == "bf-cfb");
            REQUIRE(s.plugin.toStdString() == "obfs-local");
            REQUIRE(s.plugin_options.toStdString() == "obfs=http;obfs-host=google.com");
        }
        WHEN("another url with sip003 plugin and remarks")
        {
            auto c = ss.DeserializeOutbound(
                "ss://YmYtY2ZiOnRlc3Q@192.168.1.1:8388/?plugin=obfs-local%3bobfs%3dhttp%3bobfs-host%3dgoogle.com#example-server", &alias, &err);
            s = ShadowSocksServerObject::fromJson(c.second);
            REQUIRE(s.address.toStdString() == "192.168.1.1");
            REQUIRE(s.port == 8388);
            REQUIRE(s.password.toStdString() == "test");
            REQUIRE(s.method.toStdString() == "bf-cfb");
            REQUIRE(s.plugin.toStdString() == "obfs-local");
            REQUIRE(s.plugin_options.toStdString() == "obfs=http;obfs-host=google.com");
        }
    }
}
