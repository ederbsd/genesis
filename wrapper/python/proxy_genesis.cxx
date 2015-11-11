
#include <genesis/genesis.hxx>
#include <genesis/geometry.hxx>
#include <genesis/cmd_line_parser.hxx>

#include <string>

class proxy_genesis {
  public:
    void details() {
      genesis::library::check_build_details();
    }

    void compute_geodist( double lat1, double lon1, double lat2,
                          double lon2, const char* unit ) {
      m_distance = 0.0;
      std::string str(unit);
      genesis::geometry::geodist(lat1, lon1, lat2,
                                 lon2, &this->m_distance, str);
    }

    double print_geodist() {
      return this->m_distance;
    }

    void set_value(const char* value) {
      m_value = value;
    }

    const char* print_value() {
      return m_value;
    }

    private:
      double m_distance;
      const char* m_value;
};

class proxy_genesis_cmd_line_parser {
  public:
    void add_usage( const char* desc ) {
      genesis::cmd_line_parser cmd;
      const std::string sdesc(desc);
      cmd.add_usage(sdesc);
    }

    void print_usage() {
      genesis::cmd_line_parser cmd;
      cmd.print_usage();
    }
};

extern "C" {
    proxy_genesis* proxy_genesis_new() { 
      return new proxy_genesis(); 
    }

    void proxy_genesis_details(proxy_genesis* genesis) { 
      genesis->details(); 
    }

    void proxy_genesis_compute_geodist(proxy_genesis* genesis, double lat1, 
                                       double lon1, double lat2, 
                                       double lon2, const char* unit) {
      genesis->compute_geodist(lat1, lon1, lat2, lon2, unit);
    }

    double proxy_genesis_print_geodist(proxy_genesis* genesis) {
      return genesis->print_geodist();
    } 

    void proxy_genesis_set_value(proxy_genesis* genesis, const char* value) {
      genesis->set_value(value);
    }

    const char* proxy_genesis_print_value(proxy_genesis* genesis) {
      return genesis->print_value();
    }

    void proxy_genesis_add_usage(proxy_genesis_cmd_line_parser* genesis, 
                                 const char* desc) {
      genesis->add_usage(desc);
    }

    void proxy_genesis_print_usage(proxy_genesis_cmd_line_parser* genesis) {
      genesis->print_usage();
    }
}

