using System.Configuration;

namespace EmailSteve
{
    public class ControllerElement : ConfigurationElement
    {
        [ConfigurationProperty("name", IsRequired = true)]
        public string Name { get { return this["name"] as string; } }
        [ConfigurationProperty("ipAddress", IsRequired = true)]
        public string IpAddress { get { return this["ipAddress"] as string; } }
        [ConfigurationProperty("port", IsRequired = true)]
        public string Port { get { return this["port"] as string; } }
        [ConfigurationProperty("user", IsRequired = true)]
        public string User { get { return this["user"] as string; } }
        [ConfigurationProperty("pwd", IsRequired = true)]
        public string Pwd { get { return this["pwd"] as string; } }
        [ConfigurationProperty("remotePath", IsRequired = true)]
        public string RemotePath { get { return this["remotePath"] as string; } }
        [ConfigurationProperty("filePrefix", IsRequired = true)]
        public string FilePrefix { get { return this["filePrefix"] as string; } }
        [ConfigurationProperty("protocol", IsRequired = true)]
        public string Protocol { get { return this["protocol"] as string; } }
        [ConfigurationProperty("sshFingerPrint", IsRequired = true)]
        public string SshFingerPrint { get { return this["sshFingerPrint"] as string; } }
    }

    public class ControllerCollection : ConfigurationElementCollection
    {
        public ControllerElement this[int index]
        {
            get { return base.BaseGet(index) as ControllerElement; }
            set
            {
                if (base.BaseGet(index) != null)
                    base.BaseRemoveAt(index);
                this.BaseAdd(index, value);
            }
        }

        protected override ConfigurationElement CreateNewElement()
        {
            return new ControllerElement();
        }

        protected override object GetElementKey(ConfigurationElement element)
        {
            return ((ControllerElement)element).Name;
        }
    }

    public class ControllerSection : ConfigurationSection
    {
        [ConfigurationProperty("controllers")]
        public ControllerCollection Controllers
        {
            get { return this["controllers"] as ControllerCollection; }
        }

        public static ControllerSection GetConfig()
        {
            return ConfigurationManager.GetSection("ControllersSection") as ControllerSection ?? new ControllerSection();
        }
    }
}
