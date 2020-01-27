import unittest
import os
from shutil import rmtree
from abc import ABC

import z5py


class FileTestMixin(ABC):
    def setUp(self):
        self.path = 'file.%s' % self.data_format

    def tearDown(self):
        try:
            rmtree(self.path)
        except OSError:
            pass

    def test_context_manager(self):
        self.assertFalse(os.path.exists(self.path))

        with z5py.File(self.path) as f:
            self.assertIsInstance(f, z5py.File)
            if self.data_format == 'n5':
                self.assertFalse(f.is_zarr)
            else:
                self.assertTrue(f.is_zarr)
        self.assertTrue(os.path.exists(self.path))

    def test_extension_detect(self):
        self.assertFalse(os.path.exists(self.path))

        f = z5py.File(self.path, use_zarr_format=None)
        if self.data_format == 'n5':
            self.assertFalse(f.is_zarr)
        else:
            self.assertTrue(f.is_zarr)

    def test_wrong_ext_fails(self):
        is_n5 = self.data_format == 'n5'
        with self.assertRaises(RuntimeError):
            z5py.File(self.path, use_zarr_format=is_n5)

    def test_filename(self):
        f = z5py.File(self.path)
        self.assertEqual(f.filename, self.path)

    def test_parent(self):
        f = z5py.File(self.path)
        self.assertIs(f, f.parent)

    def test_name(self):
        f = z5py.File(self.path)
        self.assertEqual(f.name, '/')


class TestZarrFile(FileTestMixin, unittest.TestCase):
    data_format = 'zarr'

    def test_direct_constructor(self):
        self.assertFalse(os.path.exists(self.path))
        f = z5py.ZarrFile(self.path)
        self.assertTrue(f.is_zarr)


class TestZrFile(FileTestMixin, unittest.TestCase):
    data_format = 'zr'

    def test_direct_constructor(self):
        self.assertFalse(os.path.exists(self.path))
        f = z5py.ZarrFile(self.path)
        self.assertTrue(f.is_zarr)


class TestN5File(FileTestMixin, unittest.TestCase):
    data_format = 'n5'

    def test_direct_constructor(self):
        self.assertFalse(os.path.exists(self.path))
        f = z5py.N5File(self.path)
        self.assertFalse(f.is_zarr)


if __name__ == '__main__':
    unittest.main()
