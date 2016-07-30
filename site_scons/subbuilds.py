class StringArray(list):
    def __init__(self):
        super(StringArray, self).__init__()

    def __iadd__(self, item):
        self.append(item)
        return self

    def append(self, item):
        if isinstance(item, str):
            #Dir('.').path + item
            super(StringArray, self).append(item)
        elif isinstance(item, list):
            for list_item in item:
                self.append(list_item)
        else:
            raise Exception("Unable to append anything but strings or lists.")

if __name__ == '__main__':
    a = StringArray()
    a += 'hello'
    assert('hello' in a)
    a += ['world']
    assert(['hello','world'] == a)
