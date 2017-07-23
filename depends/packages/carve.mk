package=carve
$(package)_version=5.3.4
$(package)_download_path=https://codeload.github.com/bitbaba/carve/tar.gz
$(package)_download_file=5.3.4
$(package)_file_name=$(package)-$($(package)_version).tar.gz
$(package)_sha256_hash=92e8d4b4d4244a40c231ff34446076ed07a34d3c52342f71710d738eab379e27

define $(package)_preprocess_cmds
  ./autogen.sh
endef

define $(package)_set_vars
  $(package)_config_opts=--with-pic
endef

define $(package)_config_cmds
  $($(package)_autoconf)
endef

define $(package)_build_cmds
  $(MAKE)
endef

define $(package)_stage_cmds
  $(MAKE) DESTDIR=$($(package)_staging_dir) install
endef

define $(package)_postprocess_cmds
endef
